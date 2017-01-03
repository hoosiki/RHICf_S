#include "G4UIcommand.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "RHICfPrimaryGeneratorMessenger.hh"
#include "RHICfPrimaryGeneratorAction.hh"

RHICfPrimaryGeneratorMessenger::RHICfPrimaryGeneratorMessenger (RHICfPrimaryGeneratorAction* genaction): primaryAction(genaction)
{
  mydetdir = new G4UIdirectory("/rhicf/");
  mydetdir-> SetGuidance("RHICf simulation control commands.");

  select= new G4UIcmdWithAString("/rhicf/generator", this);
  select-> SetGuidance("select generator");
  select-> SetParameterName("generator_type", false, false);
  select-> SetCandidates("EPOS_LHC EPOS_1.99 QGSJETII-04 QGSJETII-03 DPMJet3.0-6 Pythia8.215 ParticleGun");
  select-> SetDefaultValue("EPOS_LHC");
}

RHICfPrimaryGeneratorMessenger::~RHICfPrimaryGeneratorMessenger()
{
  delete select;
  delete mydetdir;
  delete dir;
}

void RHICfPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,
                                              G4String newValues)
{
  if ( command == select ) {
    primaryAction-> SetGenerator(newValues);
    G4cout << "current generator type: "
            << primaryAction-> GetGeneratorName() << G4endl;
  }
}


G4String RHICfPrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand* command)
{
  G4String cv, st;
  if(command==select) {
    cv=primaryAction->GetGeneratorName();
  }

 return cv;
}
