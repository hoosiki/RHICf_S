#ifndef LHCFRUNACTION_H
#define LHCFRUNACTION_H 1

#include "G4UserRunAction.hh"
#include "G4Timer.hh"
#include "G4String.hh"
#include "globals.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "RunInfo.hpp"
#include "RHICfSimEvent.hpp"

#include "RHICfDetectorConstruction.hh"

class G4Run;
class RHICfRunAction: public G4UserRunAction
{
public:
  RHICfRunAction(RHICfDetectorConstruction* det);
  ~RHICfRunAction();

  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void SetCRMC(G4String fcrmc);

  void SetOutput(std::string afdir) { fdir=afdir; };
  inline TFile* GetOutputROOTFile() const {return fout;};
  inline TTree* GetEventTree() const {return tevent;};

  inline void SetCRMCpath(G4String acrmc) {fcrmc=acrmc;};

  void SetHepMCFile(G4String aftmp) {ftmp=aftmp;};
  G4String GetHepMCFile() {return ftmp;};

  void SetRunNumber(G4int anrun) {nrun=anrun;};
  void SetNevent(G4int anevent) {nevent=anevent;};
  void SetSeed1(G4int aseed1) {seed1=aseed1;};
  void SetSeed2(G4int aseed2) {seed2=aseed2;};
  void SetFlag_Detector(Flag aflag_detector) {flag_detector=aflag_detector;};
  void SetFlag_Original(Flag aflag_original) {flag_original=aflag_original;};
  void SetModel(G4String agenname) {genname=agenname;};

  Flag GetFlag_Detector() {return flag_detector;};
  Flag GetFlag_Original() {return flag_original;};

  void SetSimEvent(RHICfSimEvent* asimEvent) {simEvent=asimEvent;};

private:
  G4Timer* fTimer; 
  G4double fElapsedTime;

  std::string fdir;
  TFile *fout;
  TTree *trun;
  TTree *tevent;

  G4String fcrmc;
  G4String ftmp;
  G4String model;
  G4int seed1;
  G4int seed2;
  G4int nevent;
  G4int nrun;
  Flag flag_detector;
  Flag flag_original;
  Flag flag_merged;
  G4String genname;

  RunInfo* runInfo;
  RHICfSimEvent* simEvent;

  RHICfDetectorConstruction* fDetector;
  /*
  CentralContainer* centralContainer;
  ForwardContainer* forwardContainer;
  MCDataContainer* mcdataContainer;
  ZDCContainer* zdcContainer;
  */
};

#endif
