#ifndef RHICFPRIMARYGENERATORMESSENGER_H
#define RHICFPRIMARYGENERATORMESSENGER_H 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class RHICfPrimaryGeneratorAction;

class RHICfPrimaryGeneratorMessenger : public G4UImessenger {
public:
  RHICfPrimaryGeneratorMessenger(RHICfPrimaryGeneratorAction* genaction);
  ~RHICfPrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand* command, G4String newValues);
  G4String GetCurrentValue(G4UIcommand* command);

private:
  RHICfPrimaryGeneratorAction* primaryAction;

  G4UIdirectory* dir;
  G4UIdirectory* mydetdir;
  G4UIcmdWithAString* select;

};

#endif
