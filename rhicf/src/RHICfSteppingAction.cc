#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"

#include "RHICfSteppingAction.hh"
#include "RHICfTrackInformation.hh"
#include "RHICfBBCSD.hh"

#include <fstream>
#include <iomanip>

//#define DUMPTRACK

//////////
/// Constructor and Destructor
RHICfSteppingAction::RHICfSteppingAction()
{
}

RHICfSteppingAction::~RHICfSteppingAction()
{
}

//////////
/// UserSteppingAction
void RHICfSteppingAction::UserSteppingAction(const G4Step* astep)
{
#ifdef DUMPTRACK
  std::ofstream of("steps.log", std::ios::out | std::ios::app );

  G4Track* track=astep->GetTrack();
  G4StepPoint* preStep=astep->GetPreStepPoint();
  G4VPhysicalVolume* prePV=preStep->GetPhysicalVolume();
  G4StepPoint* postStep=astep->GetPostStepPoint();
  G4VPhysicalVolume* postPV=postStep->GetPhysicalVolume();

  of << track->GetTrackID() << " "
     << track->GetParentID() << " "
     << track->GetDynamicParticle()->GetPDGcode() << " "
     << preStep->GetMomentum().x() << " "
     << preStep->GetMomentum().y() << " "
     << preStep->GetMomentum().z() << " "
     << preStep->GetPosition().x() << " "
     << preStep->GetPosition().y() << " "
     << preStep->GetPosition().z() << " "
     << prePV->GetName() << " "
     << postStep->GetPosition().x() << " "
     << postStep->GetPosition().y() << " "
     << postStep->GetPosition().z() << " ";
  if(!postPV) of << "Vol_world_PV" << G4endl;
  else        of << postPV->GetName() << G4endl;

  of.close();
#endif
}
