#ifndef RHICFEVENTACTION_H
#define RHICFEVENTACTION_H 1

#include "G4UserEventAction.hh"

#include "RHICfParam.hpp"

class G4Event;

class RHICfEventAction: public G4UserEventAction
{
public:
  RHICfEventAction();
  virtual ~RHICfEventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:
};

#endif
