#ifndef LHCFSTEPPINGACTION_H
#define LHCFSTEPPINGACTION_H 1

#include "G4UserSteppingAction.hh"

#include <map>

class RHICfSteppingAction: public G4UserSteppingAction
{
public:
  RHICfSteppingAction();
  ~RHICfSteppingAction();

  void UserSteppingAction(const G4Step*);

private:

};

#endif
