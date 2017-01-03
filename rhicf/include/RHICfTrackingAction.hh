#ifndef LHCFTRACKINGACTION_H
#define LHCFTRACKINGACTION_H 1

#include "G4UserTrackingAction.hh"

class RHICfTrackingAction: public G4UserTrackingAction
{
public:
  RHICfTrackingAction();
  ~RHICfTrackingAction();

  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
};

#endif
