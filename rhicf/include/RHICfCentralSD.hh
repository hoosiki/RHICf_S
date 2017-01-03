#ifndef RHICFCENTRALSD_H
#define RHICFCENTRALSD_H 1

#include "G4VSensitiveDetector.hh"

#include <vector>

#include "RHICfCentralHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class RHICfCentralSD: public G4VSensitiveDetector
{
public:
  RHICfCentralSD(const G4String name);
  virtual ~RHICfCentralSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void Initialize(G4HCofThisEvent* HCTE);
  virtual void EndOfEvent(G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 

  void SetCuts(G4double aetacut, G4double aecut, bool aopposite);

private:
  CentralHitsCollection*  hitsColl;

  G4double etacut;
  G4double ecut;
  bool opposite;
};

#endif
