#ifndef STACKINGACTION_H
#define STACKINGACTION_H 1

#include "G4UserStackingAction.hh"

class RHICfStackingAction: public G4UserStackingAction
{
public:
  RHICfStackingAction();
  virtual ~RHICfStackingAction();

  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

  private:
};

#endif
