#ifndef RHICFFORWARDSD_H
#define RHICFFORWARDSD_H 1

#include "G4VSensitiveDetector.hh"

#include <vector>

#include "RHICfForwardHit.hh"
#include "RHICfTrajectory.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class RHICfForwardSD: public G4VSensitiveDetector
{
public:
  RHICfForwardSD(const G4String name);
  virtual ~RHICfForwardSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void Initialize(G4HCofThisEvent* HCTE);
  virtual void EndOfEvent(G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 

  RHICfTrajectory* GetParentTrajectory(G4int parentID);
  G4int IsBackground(G4String aprocess);

private:
  ForwardHitsCollection*  hitsColl;
};

#endif
