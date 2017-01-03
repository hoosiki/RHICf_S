#ifndef RUNINFO_HPP
#define RUNINFO_HPP

#include <cstring>

#include "TObject.h"
#include "Flag.hpp"

class RunInfo: public TObject
{
public:
  RunInfo();
  ~RunInfo();
  void SetRunNumber(int aRunNumber);
  void SetNumberOfEvents(int aNumberOfEvents);
  void SetModel(std::string aModel);
  void SetSeed1(int aSeed1);
  void SetSeed2(int aSeed2);
  void SetFlag(Flag aflag);
  void SetSigTot(double asigTot);
  void SetSigEla(double asigEla);
  void SetSigIne(double asigIne);

  int GetRunNumber();
  int GetNumberOfEvents();
  std::string GetModel();
  int GetSeed1();
  int GetSeed2();
  Flag GetFlag();
  double GetSigTot();
  double GetSigEla();
  double GetSigIne();

private:
  int RunNumber;
  int NumberOfEvents;
  std::string Model;
  int Seed1;
  int Seed2;
  Flag flag;
  double sigTot;
  double sigEla;
  double sigIne;

  ClassDef(RunInfo, 1)
};

#endif
