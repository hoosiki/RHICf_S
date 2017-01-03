#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4Polyline.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
#include "G4DynamicParticle.hh"
#include "G4PrimaryParticle.hh"
#include "G4VProcess.hh"

#include "RHICfTrajectory.hh"
#include "RHICfTrackInformation.hh"

G4ThreadLocal G4Allocator<RHICfTrajectory> * myTrajectoryAllocator=0;

RHICfTrajectory::RHICfTrajectory(const G4Track* aTrack): G4VTrajectory(), fPositionRecord(0), fParticleDefinition(0)
{
  fParticleDefinition=aTrack->GetDefinition();
  fParticleName=fParticleDefinition->GetParticleName();
  fPDGCharge=fParticleDefinition->GetPDGCharge();
  fPDGEncoding=fParticleDefinition->GetPDGEncoding();
  if(fParticleName=="unknown") {
    G4PrimaryParticle*pp=aTrack->GetDynamicParticle()->GetPrimaryParticle();
    if(pp) {
      if(pp->GetCharge()<DBL_MAX) fPDGCharge=pp->GetCharge();
      fPDGEncoding=pp->GetPDGcode();
      if(pp->GetG4code()!=0) {
	fParticleName += " : ";
	fParticleName += pp->GetG4code()->GetParticleName();
      }
    }
  }
  fTrackID=aTrack->GetTrackID();
  fParentID=aTrack->GetParentID();
  fPositionRecord=new RHICfTrajectoryPointContainer();
  fPositionRecord->push_back(new G4TrajectoryPoint(aTrack->GetPosition()));
  fMomentum=aTrack->GetMomentum();
  fVertexPosition=aTrack->GetPosition();
  fGlobalTime=aTrack->GetGlobalTime();
  if(aTrack->GetCreatorProcess()!=NULL)
    fProduction=aTrack->GetCreatorProcess()->GetProcessName();
  else
    fProduction="Source";
}

RHICfTrajectory::~RHICfTrajectory()
{
  size_t i;
  for(i=0;i<fPositionRecord->size();i++) {
    delete (*fPositionRecord)[i];
  }
  fPositionRecord->clear();

  delete fPositionRecord;
}


void RHICfTrajectory::ShowTrajectory(std::ostream& os) const
{
  os << G4endl << "TrackID =" << fTrackID 
     << " : ParentID=" << fParentID
     << " : Process=" << fProduction
     << G4endl;
  os << "Particle name : " << fParticleName
     << "  PDG code : " << fPDGEncoding
     << "  Charge : " << fPDGCharge << G4endl;
  os << "Original momentum : " << G4BestUnit(fMomentum,"Energy")
     << G4endl;
  os << "Vertex : " << G4BestUnit(fVertexPosition,"Length")
     << "  Global time : " << G4BestUnit(fGlobalTime,"Time")
     << G4endl;
  os << "  Current trajectory has " << fPositionRecord->size() 
     << " points." << G4endl;

  for(size_t i=0; i < fPositionRecord->size(); i++) {
    G4TrajectoryPoint* aTrajectoryPoint=(G4TrajectoryPoint*)((*fPositionRecord)[i]);
    os << "Point[" << i << "]" 
       << " Position= " << aTrajectoryPoint->GetPosition()
       << G4endl;
  }
}

void RHICfTrajectory::DrawTrajectory() const
{
}

const std::map<G4String,G4AttDef>* RHICfTrajectory::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store=G4AttDefStore::GetInstance("RHICfTrajectory",isNew);
  if(isNew) {
    G4String id("ID");
    (*store)[id]=G4AttDef(id,"Track ID","Bookkeeping","","G4int");

    G4String pid("PID");
    (*store)[pid]=G4AttDef(pid,"Parent ID","Bookkeeping","","G4int");

    G4String pn("PN");
    (*store)[pn]=G4AttDef(pn,"Particle Name","Bookkeeping","","G4String");

    G4String ch("Ch");
    (*store)[ch]=G4AttDef(ch,"Charge","Physics","e+","G4double");

    G4String pdg("PDG");
    (*store)[pdg]=G4AttDef(pdg,"PDG Encoding","Bookkeeping","","G4int");

    G4String imom("IMom");
    (*store)[imom]=G4AttDef(imom, "Momentum of track at start of trajectory",
                              "Physics","G4BestUnit","G4ThreeVector");

    G4String imag("IMag");
    (*store)[imag]=
      G4AttDef(imag, "Magnitude of momentum of track at start of trajectory",
               "Physics","G4BestUnit","G4double");

    G4String vtxPos("VtxPos");
    (*store)[vtxPos]=G4AttDef(vtxPos, "Vertex position",
				"Physics","G4BestUnit","G4ThreeVector");

    G4String ntp("NTP");
    (*store)[ntp]=G4AttDef(ntp,"No. of points","Bookkeeping","","G4int");

    G4String iproduction("Production");
    (*store)[ntp]=G4AttDef(iproduction,"Production","Bookkeeping","","G4String");
  }
  return store;
}

std::vector<G4AttValue>* RHICfTrajectory::CreateAttValues() const
{
  std::vector<G4AttValue>* values=new std::vector<G4AttValue>;

  values->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fTrackID),""));
  values->push_back(G4AttValue("PID",G4UIcommand::ConvertToString(fParentID),""));
  values->push_back(G4AttValue("PN",fParticleName,""));
  values->push_back(G4AttValue("Ch",G4UIcommand::ConvertToString(fPDGCharge),""));
  values->push_back(G4AttValue("PDG",G4UIcommand::ConvertToString(fPDGEncoding),""));
  values->push_back(G4AttValue("IMom",G4BestUnit(fMomentum,"Energy"),""));
  values->push_back(G4AttValue("IMag",G4BestUnit(fMomentum.mag(),"Energy"),""));
  values->push_back(G4AttValue("VtxPos",G4BestUnit(fVertexPosition,"Length"),""));
  values->push_back(G4AttValue("NTP",G4UIcommand::ConvertToString(GetPointEntries()),""));
  values->push_back(G4AttValue("Production",G4UIcommand::ConvertToString(GetProduction()),""));

  return values;
}

void RHICfTrajectory::AppendStep(const G4Step* aStep)
{
  fPositionRecord->push_back(new G4TrajectoryPoint(aStep->GetPostStepPoint()->GetPosition()));
}

void RHICfTrajectory::MergeTrajectory(G4VTrajectory* secondTrajectory)
{
  if(!secondTrajectory) return;

  RHICfTrajectory* seco=(RHICfTrajectory*)secondTrajectory;
  G4int ent=seco->GetPointEntries();
  //
  // initial point of the second trajectory should not be merged
  for(int i=1;i<ent;i++) {
    fPositionRecord->push_back((*(seco->fPositionRecord))[i]);
  }
  delete (*seco->fPositionRecord)[0];
  seco->fPositionRecord->clear();
}
