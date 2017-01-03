#include <iostream>

#include "ZDCContainer.hpp"

ZDCContainer::ZDCContainer()
{
}

ZDCContainer::~ZDCContainer()
{
}

void ZDCContainer::Reset()
{
  zdc.clear();
  zdc.resize(nzdc);
  nphoton.clear();
  nphoton.resize(nzdc);

  smd.clear();
  smd.resize(nxy);
  for(int ixy=0; ixy<nxy; ixy++) {
    smd[ixy].resize(nsmd[ixy]);
  }

  scin.clear();
  scin.resize(nscin);
}


int ZDCContainer::GetMaxModule()
{
  double tmp=0.;
  int maxzdc=-1;
  for(unsigned int izdc=0; izdc<nzdc; izdc++) {
    if(tmp<zdc[izdc]) {
      tmp=zdc[izdc];
      maxzdc=izdc;
    }
  }
  return maxzdc;
}

double ZDCContainer::GetSumModule()
{
  double SumdE=0.;
  for(unsigned int izdc=0; izdc<nzdc; izdc++) 
    SumdE+=zdc[izdc];

  return SumdE;
}

void ZDCContainer::SetZDC(int azdc, double aedep)
{ zdc[azdc]=aedep; }
void ZDCContainer::SetNphoton(int azdc, int anphoton)
{ nphoton[azdc]=anphoton; }
void ZDCContainer::SetSMD(int axy, int asmd, double aedep)
{ smd[axy][asmd]=aedep; }
void ZDCContainer::SetScin(int ascin, double aedep)
{ scin[ascin]=aedep; }

std::vector<double> ZDCContainer::GetZDC()
{ return zdc; }
std::vector<int> ZDCContainer::GetNphoton()
{ return nphoton; }
std::vector<std::vector<double> > ZDCContainer::GetSMD()
{ return smd; }
std::vector<double> ZDCContainer::GetScin()
{ return scin; }
