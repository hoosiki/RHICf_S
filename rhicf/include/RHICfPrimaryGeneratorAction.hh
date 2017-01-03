#ifndef RHICFPRIMARYGENERATORACTION_H
#define RHICFPRIMARYGENERATORACTION_H 1

#include <map>

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#include "TFile.h"
#include "TTree.h"

#include "RHICfSimEvent.hpp"
#include "Flag.hpp"

class G4Event;
class G4VPrimaryGenerator;
class RHICfPrimaryGeneratorMessenger;

class RHICfPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  RHICfPrimaryGeneratorAction();
  ~RHICfPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* anEvent);

  void SetGenerator(G4VPrimaryGenerator* gen);
  void SetGenerator(G4String genname);
  void SetFlag(Flag aflag);
  void SetInput(TFile *afin);
  void SetInteractiveFlag(G4String isInteractive);
  void SetBeam(G4String aParticle, G4double aEnergy, G4String aPosition, G4double aDetPosition);

  G4VPrimaryGenerator* GetGenerator() const;
  G4String GetGeneratorName() const;
  G4VPrimaryGenerator* GetHepMCReader() {return hepmcAscii;};
  CentralContainer* GetCentral() {return centralCont;};
  ForwardContainer* GetForward() {return forwardCont;};
  std::multimap<G4int, G4int> GetCentralID() {return CentralID;};

  G4int GetProcess() {return gprocess;};

  void SetCuts(G4double aetacut, G4double aecut, bool aopposite);
  bool CheckHit(G4double x, G4double y, G4String phit);

  Forward* GetBeam() {return BeamInfo;};

private:
  G4VPrimaryGenerator* particleGun;
  G4VPrimaryGenerator* hepmcAscii;

  G4VPrimaryGenerator* currentGenerator;
  G4String currentGeneratorName;
  std::map<G4String, G4VPrimaryGenerator*> gentypeMap;
  bool finteractive;
  TFile *fin;
  TTree *tin;
  Flag flag;
  std::vector<Central*> central;
  CentralContainer *centralCont;
  std::vector<Forward*> forward;
  ForwardContainer *forwardCont;
  std::multimap<G4int, G4int> CentralID; // 1st: New TrackID; 2nd: Original TrackID

  G4int gprocess;

  G4double etacut;
  G4double ecut;
  bool opposite;

  G4String bParticle;
  G4double bEnergy;
  G4String bPosition;
  G4double DetPosition;

  Forward* BeamInfo;

  RHICfPrimaryGeneratorMessenger* messenger;
};

inline void RHICfPrimaryGeneratorAction::SetGenerator(G4VPrimaryGenerator* gen)
{
  currentGenerator = gen;
}

inline void RHICfPrimaryGeneratorAction::SetGenerator(G4String genname)
{
  std::map<G4String, G4VPrimaryGenerator*>::iterator pos=gentypeMap.find(genname);
  if(pos!=gentypeMap.end()) {
    currentGenerator=pos->second;
    currentGeneratorName=genname;
  }
}

inline G4VPrimaryGenerator* RHICfPrimaryGeneratorAction::GetGenerator() const
{
  return currentGenerator;
}

inline G4String RHICfPrimaryGeneratorAction::GetGeneratorName() const
{
  return currentGeneratorName;
}

inline void RHICfPrimaryGeneratorAction::SetBeam(G4String aParticle, G4double aEnergy, G4String aPosition, G4double aDetPosition)
{
  bParticle=aParticle;
  bEnergy=aEnergy;
  bPosition=aPosition;
  DetPosition=aDetPosition;
}

#endif
