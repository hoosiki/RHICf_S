#include <iostream>

#include "MCDataContainer.hpp"

MCDataContainer::MCDataContainer()
{
}

MCDataContainer::~MCDataContainer()
{
}


void MCDataContainer::Reset()
{
  RecoDataContainer::Reset();

  bar_truth.clear();
  bar_truth.resize(ntower);
  for(int itower=0; itower<ntower; itower++) {
    bar_truth[itower].resize(nbelt);
    for(int ibelt=0; ibelt<nbelt; ibelt++) {
      bar_truth[itower][ibelt].resize(nxy);
      for(int ixy=0; ixy<nxy; ixy++) {
	bar_truth[itower][ibelt][ixy].resize(nbar[itower]);
      }
    }
  }

  plate_truth.clear();
  plate_truth.resize(ntower);
  for(int itower=0; itower<ntower; itower++) {
    plate_truth[itower].resize(nplate);
  }
}

void MCDataContainer::SetBarTruth(int atower, int abelt, int axy, int abar, double aedep)
{
  bar_truth[atower][abelt][axy][abar]=aedep;
}

std::vector<std::vector<std::vector<std::vector<double> > > > MCDataContainer::GetBarTruth()
{
  return bar_truth;
}

void MCDataContainer::SetPlateTruth(int atower, int aplate, double aedep)
{
  plate_truth[atower][aplate]=aedep;
}

std::vector<std::vector<double> > MCDataContainer::GetPlateTruth()
{
  return plate_truth;
}

