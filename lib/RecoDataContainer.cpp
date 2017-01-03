#include <iostream>

#include "RecoDataContainer.hpp"

RecoDataContainer::RecoDataContainer()
{
}

RecoDataContainer::~RecoDataContainer()
{
}

void RecoDataContainer::Reset()
{
  plate.clear();
  plate.resize(ntower);
  for(int itower=0; itower<ntower; itower++) {
    plate[itower].resize(nplate);
  }

  bar.clear();
  bar.resize(ntower);
  for(int itower=0; itower<ntower; itower++) {
    bar[itower].resize(nbelt);
    for(int ibelt=0; ibelt<nbelt; ibelt++) {
      bar[itower][ibelt].resize(nxy);
      for(int ixy=0; ixy<nxy; ixy++) {
	bar[itower][ibelt][ixy].resize(nbar[itower]);
      }
    }
  }

  unused.clear();
  unused.resize(nbelt);
  for(int ibelt=0; ibelt<nbelt; ibelt++) {
    unused[ibelt].resize(nxy);
    for(int ixy=0; ixy<nxy; ixy++) {
      unused[ibelt][ixy].resize(nunused);
    }
  }
}


int RecoDataContainer::GetMaxBar(int atower, int abelt, int axy)
{
  double tmp=0.;
  int maxbar=-1;
  for(unsigned int ibar=0; ibar<nbar[atower];ibar++) {
    if(tmp<bar[atower][abelt][axy][ibar]) {
      tmp=bar[atower][abelt][axy][ibar];
      maxbar=ibar;
    }
  }
  return maxbar;
}

double RecoDataContainer::GetBeltSum(int atower, int abelt, int axy)
{
  double SumdE=0.;
  for(unsigned int ibar=0; ibar<nbar[atower];ibar++) {
    SumdE+=bar[atower][abelt][axy][ibar];
  }
  return SumdE;
}

double RecoDataContainer::GetLayerSum(int atower, int abelt)
{
  double SumdE=0.;
  for(int ixy=0; ixy<nxy; ixy++) {
    SumdE+=GetBeltSum(atower, abelt, ixy);
  }
  return SumdE;
}

int RecoDataContainer::GetMaxLayerSum(int atower, double thr=0.)
{
  double tmpdE=thr;
  int maxlayer=-1;
  for(int ibelt=0; ibelt<nbelt; ibelt++) {
    if(tmpdE<GetLayerSum(atower, ibelt)) {
      tmpdE=GetLayerSum(atower, ibelt);
      maxlayer=ibelt;
    }
  }
  if(tmpdE<thr && maxlayer==-1) {
    if(0) std::cerr << "No max layer" << std::endl;
  }
  return maxlayer;
}

void RecoDataContainer::SetPlate(int atower, int aplate, double aedep)
{
  plate[atower][aplate]=aedep;
}

void RecoDataContainer::SetBar(int atower, int abelt, int axy, int abar, double aedep)
{
  bar[atower][abelt][axy][abar]=aedep;
}

void RecoDataContainer::SetUnused(int abelt, int axy, int aunused, double aedep)
{
  unused[abelt][axy][aunused]=aedep;
}

std::vector<std::vector<double> > RecoDataContainer::GetPlate()
{
  return plate;
}

std::vector<std::vector<std::vector<std::vector<double> > > > RecoDataContainer::GetBar()
{
  return bar;
}

std::vector<std::vector<std::vector<double> > > RecoDataContainer::GetUnused()
{
  return unused;
}
