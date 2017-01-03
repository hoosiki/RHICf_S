#include "RomanPotContainer.hpp"

RomanPotContainer::RomanPotContainer()
{
}

RomanPotContainer::~RomanPotContainer()
{
}

void RomanPotContainer::Push_back(RomanPot* aromanpot)
{
  romanpotCont.push_back(aromanpot);
}

void RomanPotContainer::Reset()
{
  for(unsigned int i=0; i<romanpotCont.size(); i++) 
    delete romanpotCont[i];
  romanpotCont.clear();
}

std::vector<RomanPot*> RomanPotContainer::GetContainer()
{
  return romanpotCont;
}
