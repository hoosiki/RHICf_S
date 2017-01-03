#include <iomanip>

#include "G4ParticleTypes.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

#include "RHICfDetectorConstruction.hh"
#include "RHICfBBCSD.hh"

//////////
/// Constructor and Destructor
RHICfBBCSD::RHICfBBCSD(G4String name): G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname=name);
}

RHICfBBCSD::~RHICfBBCSD()
{
}

//////////
/// Initialize
void RHICfBBCSD::Initialize(G4HCofThisEvent* HCTE)
{
  /// Create hit collection
  hitsColl=new BBCHitsCollection(SensitiveDetectorName, collectionName[0]); 
  
  /// Push H.C. to "Hit Collection of This Event"
  G4int hcid=GetCollectionID(0);
  HCTE->AddHitsCollection(hcid, hitsColl);

  /// Clear energy deposit and hit particles
  edep.clear();
  part.clear();
  edep.resize(nside);
  part.resize(nside);
  for(int iside=0; iside<nside; iside++) {
    edep[iside].resize(nbbc);
    part[iside].resize(nbbc);
    for(int ibbc=0; ibbc<nbbc; ibbc++) {
      part[iside][ibbc].clear();
    }
  }
}

//////////
/// ProcessHits
G4bool RHICfBBCSD::ProcessHits(G4Step* astep, G4TouchableHistory*)
{
  /// Get step information from "PreStepPoint"
  const G4StepPoint* preStepPoint=astep->GetPreStepPoint();
  const G4StepPoint* postStepPoint=astep->GetPostStepPoint();
  G4VPhysicalVolume* prePV=preStepPoint->GetPhysicalVolume();

  G4TouchableHistory* touchable=(G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4int iside=touchable->GetReplicaNumber(3);
  G4int ibbc=touchable->GetReplicaNumber(0);
  edep[iside][ibbc]+=astep->GetTotalEnergyDeposit();

  if(prePV->GetName()=="Vol-bbc-tile-small_PV" ||
     prePV->GetName()=="Vol-bbc-tile-large_PV") {
    if(preStepPoint->GetStepStatus()==fGeomBoundary) {
      G4ThreeVector global1=preStepPoint->GetPosition();
      G4ThreeVector global2=postStepPoint->GetPosition();
      const G4AffineTransform transform=touchable->GetHistory()->GetTopTransform();
      G4ThreeVector local1=transform.TransformPoint(global1);
      G4ThreeVector local2=transform.TransformPoint(global2);
      if(local2.z()-local1.z()>0) {
	G4Track* track=astep->GetTrack();
	BBCParticle *p=new BBCParticle();
	p->SetPDGCode(track->GetDynamicParticle()->GetPDGcode());
	p->SetMomentum(TLorentzVector(track->GetMomentum().x(),
				      track->GetMomentum().y(),
				      track->GetMomentum().z(),
				      track->GetTotalEnergy()));
	part[iside][ibbc].push_back(p);
      }
    }
  }

  return true;
}

//////////
/// EndOfEvent
void RHICfBBCSD::EndOfEvent(G4HCofThisEvent* )
{
  /// Make hits and push them to "Hit Coleltion"
  for(int iside=0; iside<nside; iside++) {
    for(int ibbc=0; ibbc<nbbc; ibbc++) {
      RHICfBBCHit* ahit=new RHICfBBCHit(iside, ibbc, edep[iside][ibbc], part[iside][ibbc]);
      hitsColl->insert(ahit);
    }
  }
}

//////////
/// DrawAll
void RHICfBBCSD::DrawAll()
{
}

//////////
/// PrintAll
void RHICfBBCSD::PrintAll()
{
  hitsColl->PrintAllHits();
}
