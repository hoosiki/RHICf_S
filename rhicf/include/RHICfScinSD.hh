#ifndef RHICFSCINSD_H
#define RHICFSCINSD_H 1

#include "G4VSensitiveDetector.hh"

#include <vector>

#include "RHICfScinHit.hh"
#include "RHICfParam.hpp"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class RHICfScinSD: public G4VSensitiveDetector
{
public:
  RHICfScinSD(const G4String name);
  virtual ~RHICfScinSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void Initialize(G4HCofThisEvent* HCTE);
  virtual void EndOfEvent(G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 
  
private:
  /// Buffer for energy deposit
  std::vector<double> edep;
  ScinHitsCollection*  hitsColl;
};

#endif
