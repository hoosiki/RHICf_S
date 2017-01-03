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
#include "RHICfForwardSD.hh"
#include "RHICfTrackInformation.hh"

//////////
/// Constructor and Destructor
RHICfForwardSD::RHICfForwardSD(G4String name): G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname=name);
}

RHICfForwardSD::~RHICfForwardSD()
{
}

//////////
/// Initialize
void RHICfForwardSD::Initialize(G4HCofThisEvent* HCTE)
{
  /// Create hit collection
  hitsColl=new ForwardHitsCollection(SensitiveDetectorName, collectionName[0]); 
  
  /// Push H.C. to "Hit Collection of This Event"
  G4int hcid=GetCollectionID(0);
  HCTE->AddHitsCollection(hcid, hitsColl);
}

//////////
/// ProcessHits
G4bool RHICfForwardSD::ProcessHits(G4Step* astep, G4TouchableHistory*)
{
  G4Track* track=astep->GetTrack();

  /// Get step information from "PreStepPoint"
  const G4StepPoint* preStepPoint=astep->GetPreStepPoint();
  const G4StepPoint* postStepPoint=astep->GetPostStepPoint();
  G4VPhysicalVolume* postPV=postStepPoint->GetPhysicalVolume();

  G4ThreeVector global1=preStepPoint->GetPosition();
  G4ThreeVector global2=postStepPoint->GetPosition();
  G4TouchableHistory* touchable=(G4TouchableHistory*)(preStepPoint->GetTouchable());
  const G4AffineTransform transform=touchable->GetHistory()->GetTopTransform();
  G4ThreeVector local1=transform.TransformPoint(global1);
  G4ThreeVector local2=transform.TransformPoint(global2);
  if(local2.z()-local1.z()<0) return true;


  RHICfForwardHit* ahit=new RHICfForwardHit();

  ahit->SetPDGCode(track->GetDynamicParticle()->GetPDGcode());
  ahit->SetEnergy(track->GetTotalEnergy());
  ahit->SetEkinetic(track->GetKineticEnergy());
  ahit->SetPosition(postStepPoint->GetPosition());
  ahit->SetDirection(postStepPoint->GetMomentumDirection());

  G4int motherID=track->GetParentID();
  G4int tmp_motherID=motherID;
  if(tmp_motherID==0) tmp_motherID=track->GetTrackID();

  /// Check if there is the particle has inelastic process or not
  /// This includes bremstrahlung and conversion
  bool isbkg=false;

  G4String proc="Source";
  if(track->GetCreatorProcess()!=NULL)
    proc=track->GetCreatorProcess()->GetProcessName();
  isbkg=IsBackground(proc);

  while(motherID!=0) {
    tmp_motherID=motherID;
    RHICfTrajectory* parentTrajectory=GetParentTrajectory(motherID);
    if(parentTrajectory==0) break;
    proc=parentTrajectory->GetProduction();
    motherID=parentTrajectory->GetParentID();
    if(!isbkg) isbkg=IsBackground(proc);
  }

  ahit->SetMotherID(tmp_motherID);
  ahit->SetisBackground(isbkg);

  hitsColl->insert(ahit);

  return true;
}

//////////
/// EndOfEvent
void RHICfForwardSD::EndOfEvent(G4HCofThisEvent* )
{
}

//////////
/// DrawAll
void RHICfForwardSD::DrawAll()
{
}

//////////
/// PrintAll
void RHICfForwardSD::PrintAll()
{
  hitsColl->PrintAllHits();
}

RHICfTrajectory* RHICfForwardSD::GetParentTrajectory(G4int motherID)
{
  G4TrajectoryContainer* container=
   G4RunManager::GetRunManager()->GetCurrentEvent()->GetTrajectoryContainer();
  if(container==0) return 0;
  size_t nTraj=container->size();
  for(size_t i=0;i<nTraj;i++) {
    RHICfTrajectory* tr1=(RHICfTrajectory*)((*container)[i]);
    if(tr1->GetTrackID()==motherID) return tr1;
  }
  return 0;
}

G4int RHICfForwardSD::IsBackground(G4String aprocess)
{
  if(aprocess=="eBrem" || aprocess== "compt" ||
     aprocess=="conv"  || aprocess=="annihil" ||
     aprocess=="electronNuclear"  || aprocess=="positronNuclear" ||
     aprocess=="photonCapture"    || aprocess=="photonNuclear" ||
     aprocess=="photonFission"    || aprocess=="muonNuclear" ||
     aprocess=="pi+Inelastic"     || aprocess=="pi-Inelastic" ||
     aprocess=="kaon+Inelastic"   || aprocess=="kaon-Inelastic" ||
     aprocess=="kaon0SInelastic"  || aprocess=="kaon0LInelastic" ||
     aprocess=="protonInelastic"  || aprocess=="anti_protonInelastic" ||
     aprocess=="neutronInelastic" || aprocess=="anti_neutronInelastic" ||
     aprocess=="lambdaInelastic"  || aprocess=="anti-lambdaInelastic" ||
     aprocess=="omega-Inelastic"  || aprocess=="anti_omega-Inelastic" ||
     aprocess=="sigma-Inelastic"  || aprocess=="anti_sigma-Inelastic" ||
     aprocess=="sigma+Inelastic"  || aprocess=="anti_sigma+Inelastic" ||
     aprocess=="xi-Inelastic"     || aprocess=="anti_xi-Inelastic" ||
     aprocess=="xi0Inelastic"     || aprocess=="anti_xi0Inelastic" ||
     aprocess=="dInelastic"       || aprocess=="anti_deuteronInelastic" ||
     aprocess=="tInelastic"       || aprocess=="anti_tritonInelastic" ||
     aprocess=="he3Inelastic"     || aprocess=="anti_He3Inelastic" ||
     aprocess=="alphaInelastic"   || aprocess=="anti_alphaInelastic" ||
     aprocess=="nCapture"         || aprocess=="nFission" ||
     aprocess=="ionInelastic") {
    return true;
  }

  return false;    
}
