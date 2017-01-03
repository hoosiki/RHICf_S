#ifndef MCDATACONTAINER_HPP
#define MCDATACONTAINER_HPP

#include "RecoDataContainer.hpp"

class MCDataContainer: public RecoDataContainer
{
public:
  MCDataContainer();
  ~MCDataContainer();
  void Reset();

  /// Energy deposit From Geant4
  void SetBarTruth(int atower, int abelt, int axy, int abar, double aedep);
  std::vector<std::vector<std::vector<std::vector<double> > > > GetBarTruth();
  void SetPlateTruth(int atower, int aplate, double aedep);
  std::vector<std::vector<double> > GetPlateTruth();

private:
  std::vector<std::vector<std::vector<std::vector<double> > > > bar_truth;
  std::vector<std::vector<double> > plate_truth;

  ClassDef(MCDataContainer, 1)
};

#endif
