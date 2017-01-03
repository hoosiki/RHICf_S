#include <boost/filesystem.hpp>

#include "RHICfPrimaryGeneratorAction.hh"
#include "RHICfPrimaryGeneratorMessenger.hh"
#include "HepMCG4AsciiReader.hh"

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

namespace fs=boost::filesystem;


RHICfPrimaryGeneratorAction::RHICfPrimaryGeneratorAction()
{
  currentGenerator = particleGun= new G4ParticleGun();
  currentGeneratorName = "BeamTest";
  hepmcAscii = new HepMCG4AsciiReader();

  gentypeMap["Generate"]  = hepmcAscii;
  gentypeMap["Transport"] = particleGun;
  gentypeMap["Response"]  = particleGun;
  gentypeMap["BeamTest"]  = particleGun;

  messenger= new RHICfPrimaryGeneratorMessenger(this);
}


RHICfPrimaryGeneratorAction::~RHICfPrimaryGeneratorAction()
{
  delete messenger;
}

void RHICfPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();

  if(currentGenerator) {
    if(currentGeneratorName=="Transport") {
      tin->GetEntry(anEvent->GetEventID());
      central=centralCont->GetContainer();
      std::vector<G4ParticleGun*> particles;
      particles.clear();
      G4ParticleDefinition* part;
      G4ThreeVector pos;
      G4LorentzVector mom;
      G4double ekin;

      G4int ipart=0;
      for(unsigned int i=0; i<central.size(); i++) {
	if(!central[i]->isBoundary()) continue;
	if(opposite) {
	  if(fabs(central[i]->GetMomentum().Eta())<etacut) continue;
	}else{
	  if(central[i]->GetMomentum().Eta()<etacut)       continue;
	}
	if(central[i]->GetMomentum().E()<ecut) continue; /// both in GeV

	particles.push_back(new G4ParticleGun());
	part=G4ParticleTable::GetParticleTable()->FindParticle(central[i]->GetPDGcode());
	particles[ipart]->SetParticleDefinition(part);
	pos=G4ThreeVector(central[i]->GetPosition2().x(),
			  central[i]->GetPosition2().y(),
			  central[i]->GetPosition2().z());
	particles[ipart]->SetParticlePosition(pos);
	mom=G4LorentzVector(central[i]->GetMomentum().Vect().Unit().Px(),
			    central[i]->GetMomentum().Vect().Unit().Py(),
			    central[i]->GetMomentum().Vect().Unit().Pz());
	particles[ipart]->SetParticleMomentumDirection(mom);
	ekin=central[i]->GetMomentum().Energy();
	particles[ipart]->SetParticleEnergy(ekin*CLHEP::GeV);
	particles[ipart]->GeneratePrimaryVertex(anEvent);

	ipart++;
      }
      CentralID.clear();
      for(int i=central.size()-1; i>=0; i--) {
	if(!central[i]->isBoundary()) continue;
	if(!opposite && central[i]->GetMomentum().Eta()<0) continue;
	if(central[i]->GetMomentum().E()<ecut)  continue; /// both in GeV
	if(fabs(central[i]->GetMomentum().Eta())<etacut)   continue;

	if(central[i]->GetMotherID()==0) {
	  CentralID.insert(std::multimap<G4int, G4int>::value_type(ipart, central[i]->GetID()));
	}else{
	  CentralID.insert(std::multimap<G4int, G4int>::value_type(ipart, central[i]->GetMotherID()));
	}
	ipart--;
      }
    }else if(currentGeneratorName=="Response") {
      tin->GetEntry(anEvent->GetEventID());
      central=centralCont->GetContainer();
      forward=forwardCont->GetContainer();
      std::vector<G4ParticleGun*> particles;
      particles.clear();
      G4ParticleDefinition* part;
      G4ThreeVector pos;
      G4LorentzVector mom;
      G4double ekin;

      for(unsigned int i=0; i<forward.size(); i++) {
	particles.push_back(new G4ParticleGun());
	G4int ipart=particles.size()-1;
	part=G4ParticleTable::GetParticleTable()->FindParticle(forward[i]->GetPDGcode());
	particles[ipart]->SetParticleDefinition(part);
	pos=G4ThreeVector(forward[i]->GetPosition().x(),
			  forward[i]->GetPosition().y(),
			  forward[i]->GetPosition().z());
	particles[ipart]->SetParticlePosition(pos);
	mom=G4LorentzVector(forward[i]->GetMomentum().Vect().Unit().Px(),
			    forward[i]->GetMomentum().Vect().Unit().Py(),
			    forward[i]->GetMomentum().Vect().Unit().Pz());
	particles[ipart]->SetParticleMomentumDirection(mom);
	ekin=forward[i]->GetMomentum().Energy();
	particles[ipart]->SetParticleEnergy(ekin*CLHEP::GeV);
	particles[ipart]->GeneratePrimaryVertex(anEvent);
      }
    }else if(currentGeneratorName=="BeamTest") {
      G4ParticleTable* bTable=G4ParticleTable::GetParticleTable();
      G4ParticleDefinition* beam=bTable->FindParticle(bParticle);
      G4ThreeVector position;
      G4ThreeVector direction;

      direction=G4ThreeVector(0., 0., 1.);

      G4double xx=gRandom->Uniform(-55,55);
      G4double yy=gRandom->Uniform(-70,150);

      while(!CheckHit(xx,yy,bPosition)) {
	xx=gRandom->Uniform(-55,55);
	yy=gRandom->Uniform(-70,150);
      }

      position=G4ThreeVector(xx, yy, -10.*CLHEP::cm);

      particleGun=new G4ParticleGun(1);
      dynamic_cast<G4ParticleGun*>(particleGun)->SetParticleDefinition(beam);
      dynamic_cast<G4ParticleGun*>(particleGun)->SetParticlePosition(position);
      dynamic_cast<G4ParticleGun*>(particleGun)->SetParticleMomentumDirection(direction);
      dynamic_cast<G4ParticleGun*>(particleGun)->SetParticleEnergy(bEnergy);

      /// Set Beam information
      BeamInfo=new Forward();
      BeamInfo->SetMotherID(0);
      BeamInfo->SetPDGcode(dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleDefinition()->GetPDGEncoding());
      TLorentzVector tmp4;
      tmp4.SetPxPyPzE(dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentum()*
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentumDirection().x(),
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentum()*
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentumDirection().y(),
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentum()*
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleMomentumDirection().z(),
		      dynamic_cast<G4ParticleGun*>(particleGun)->GetParticleEnergy());
      BeamInfo->SetMomentum(tmp4);
      TVector3 tmp3;
      tmp3.SetXYZ(dynamic_cast<G4ParticleGun*>(particleGun)->GetParticlePosition().x(),
		  dynamic_cast<G4ParticleGun*>(particleGun)->GetParticlePosition().y(),
		  dynamic_cast<G4ParticleGun*>(particleGun)->GetParticlePosition().z());
      BeamInfo->SetPosition(tmp3);
      BeamInfo->SetIsBackground(false);

      particleGun->GeneratePrimaryVertex(anEvent);
    }else if(currentGeneratorName=="Generate") {
      currentGenerator->GeneratePrimaryVertex(anEvent);
      gprocess=dynamic_cast<HepMCG4AsciiReader*>(currentGenerator)->GetProcess();
    }
  }else
    G4Exception("RHICfPrimaryGeneratorAction::GeneratePrimaries",
                "PrimaryGeneratorAction", FatalException,
                "generator is not instanciated." );
}


void RHICfPrimaryGeneratorAction::SetInput(TFile *afin)
{
  fin=afin;

  tin=(TTree*)fin->Get("EventInfo");
  tin->SetMakeClass(1);

  if(currentGeneratorName=="Transport") {
    centralCont=new CentralContainer();
    tin->SetBranchAddress("central", &centralCont);
  }else if(currentGeneratorName=="Response") {
    centralCont=new CentralContainer();
    forwardCont=new ForwardContainer();
    tin->SetBranchAddress("central", &centralCont);
    tin->SetBranchAddress("forward", &forwardCont);
  }
}

void RHICfPrimaryGeneratorAction::SetCuts(G4double aetacut, G4double aecut, bool aopposite)
{
  etacut=aetacut;
  ecut=aecut;
  opposite=aopposite;
}

bool RHICfPrimaryGeneratorAction::CheckHit(G4double x, G4double y, G4String phit)
{
  G4double edge=0;
  G4int hit=-1;
  if(phit=="UNIFORM")    { return true; }
  else if(phit=="ZDC")   { hit=2; }
  else if(phit=="SMALL") { hit=0; }
  else if(phit=="LARGE") { hit=1; }

  if(hit==0 &&
     y-DetPosition<+x+(10.-edge)*sqrt(2.) &&
     y-DetPosition<-x+(10.-edge)*sqrt(2.) &&
     y-DetPosition>+x-(10.-edge)*sqrt(2.) &&
     y-DetPosition>-x-(10.-edge)*sqrt(2.)) {
    return true;
  }else if(hit==1 &&
	   y-DetPosition<+x+(50.-edge)*sqrt(2.)+5. &&
	   y-DetPosition<-x+(50.-edge)*sqrt(2.)+5. &&
	   y-DetPosition>+x+(10.+edge)*sqrt(2.)+5. &&
	   y-DetPosition>-x+(10.+edge)*sqrt(2.)+5.) {
    return true;
  }else if(hit==2 &&
	   fabs(x)<50 && y>-56 && y<80) {
    return true;
  }

  return false;
}
