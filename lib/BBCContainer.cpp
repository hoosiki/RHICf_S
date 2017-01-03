#include "BBCContainer.hpp"

#include <iostream>

BBCContainer::BBCContainer()
{
}

BBCContainer::~BBCContainer()
{
}

void BBCContainer::Reset()
{
  bbcCont.clear();
  bbcCont.resize(nside);
  for(int iside=0; iside<nside; iside++) {
    bbcCont[iside].resize(nbbc);
    for(int ibbc=0; ibbc<nbbc; ibbc++) {
      bbcCont[iside][ibbc]=new BBC();
      bbcCont[iside][ibbc]->Reset();
    }
  }
}

void BBCContainer::SetBBC(int aside, int aid, BBC* abbc)
{
  bbcCont[aside][aid]=abbc;
}

std::vector< std::vector<BBC*> > BBCContainer::GetContainer()
{
  return bbcCont;
}
