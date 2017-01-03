#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"

#include "RHICfStackingAction.hh"

//////////
/// Constructor and Destructor
RHICfStackingAction::RHICfStackingAction()
{;}

RHICfStackingAction::~RHICfStackingAction()
{;}

//////////
/// ClassifyNewTrack
G4ClassificationOfNewTrack
RHICfStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
  if(0) {
    /// Particle is secondary
    if(aTrack->GetParentID() > 0) {
      G4ParticleDefinition* particleType=aTrack->GetDefinition();
      if(particleType!=G4OpticalPhoton::OpticalPhotonDefinition()) {
	G4String proc = aTrack->GetCreatorProcess()->G4VProcess::GetProcessName();
	G4cout << "ID: " << aTrack->GetTrackID() << " "
	       << "Proc: " << proc << " "
	       << "PV: " << aTrack->GetVolume()->GetName() << " "
	       << "PV: " << aTrack->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName() << " "
	       << "Pos: " << aTrack->GetPosition().x()/CLHEP::mm << " mm, "
	       << aTrack->GetPosition().y()/CLHEP::mm << " mm, "
	       << aTrack->GetPosition().z()/CLHEP::mm << " mm "
	       << G4endl;
	if(aTrack->GetNextVolume()) {
	  G4cout << "NextPV: " << aTrack->GetNextVolume()->GetName() << G4endl;
	}
      }
    }
  }

  return fUrgent;
}

//////////
/// NewStage
void RHICfStackingAction::NewStage()
{
}

//////////
/// PrepareNewEvent
void RHICfStackingAction::PrepareNewEvent()
{
}
