#include "G4ParticleTypes.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "G4Tubs.hh"

#include "RHICfScinSD.hh"

//////////
/// Constructor and Destructor
RHICfScinSD::RHICfScinSD(G4String name): G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname=name);
}

RHICfScinSD::~RHICfScinSD()
{
}

//////////
/// Initialize
void RHICfScinSD::Initialize(G4HCofThisEvent* HCTE)
{
  /// Create hit collection
  hitsColl = new ScinHitsCollection(SensitiveDetectorName, collectionName[0]); 
  
  /// Push H.C. to "Hit Collection of This Event"
  G4int hcid = GetCollectionID(0);
  HCTE->AddHitsCollection(hcid, hitsColl);

  /// Clear energy deposit buffer
  edep.clear();
  edep.resize(nscin);
}

//////////
/// ProcessHits
G4bool RHICfScinSD::ProcessHits(G4Step* astep, G4TouchableHistory*)
{
  /// Get step information from "PreStepPoint"
  const G4StepPoint* preStepPoint=astep->GetPreStepPoint();
  G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());

  G4int iscin=touchable->GetReplicaNumber(0);

  /// Accumulate energy deposit in each scintillator
  edep[iscin]+=astep->GetTotalEnergyDeposit()/CLHEP::MeV;

  return true;
}

//////////
/// EndOfEvent
void RHICfScinSD::EndOfEvent(G4HCofThisEvent* )
{
  /// Make hits and push them to "Hit Coleltion"
  for(int iscin=0; iscin<nscin; iscin++) {
    RHICfScinHit* ahit=new RHICfScinHit(iscin, edep[iscin]);
    hitsColl->insert(ahit);
  }
}

//////////
/// DrawAll
void RHICfScinSD::DrawAll()
{
}

//////////
/// PrintAll
void RHICfScinSD::PrintAll()
{
  hitsColl->PrintAllHits();
}
