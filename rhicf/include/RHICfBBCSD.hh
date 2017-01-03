#ifndef RHICFBBCSD_H
#define RHICFBBCSD_H 1

#include "G4VSensitiveDetector.hh"

#include <vector>

#include "RHICfBBCHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class RHICfBBCSD: public G4VSensitiveDetector
{
public:
  RHICfBBCSD(const G4String name);
  virtual ~RHICfBBCSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void Initialize(G4HCofThisEvent* HCTE);
  virtual void EndOfEvent(G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 

private:
  BBCHitsCollection*  hitsColl;

  std::vector<std::vector<double> > edep;
  std::vector< std::vector<std::vector<BBCParticle*> > > part;
};

#endif
