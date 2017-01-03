#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "RHICfTrackingAction.hh"
#include "RHICfTrackInformation.hh"
#include "RHICfTrajectory.hh"

//////////
/// Constructor and Destructor
RHICfTrackingAction::RHICfTrackingAction()
{
}

RHICfTrackingAction::~RHICfTrackingAction()
{
}

//////////
/// PreUserTrackingAction
void RHICfTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  fpTrackingManager->SetStoreTrajectory(true);
  fpTrackingManager->SetTrajectory(new RHICfTrajectory(aTrack));
}

//////////
/// PostUserTrackingAction
void RHICfTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
