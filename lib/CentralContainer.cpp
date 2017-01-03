#include <iostream>

#include "CentralContainer.hpp"

CentralContainer::CentralContainer()
{
}

CentralContainer::~CentralContainer()
{
}

void CentralContainer::Push_back(Central* acentral)
{
  centralCont.push_back(acentral);
}

void CentralContainer::Reset()
{
  for(unsigned int i=0; i<centralCont.size(); i++) 
    delete centralCont[i];
  centralCont.clear();
}
std::vector<Central*> CentralContainer::GetContainer()
{
  return centralCont;
}
