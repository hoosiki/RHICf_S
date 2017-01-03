#include <iostream>

#include "BBC.hpp"

BBC::BBC()
{
  Reset();
}

BBC::BBC(const BBC& obj)
{
}

BBC::~BBC()
{
}

void BBC::Reset()
{
  edep=0.;
  for(unsigned int i=0; i<bbchit.size(); i++) 
    delete bbchit[i];
  bbchit.clear();
}

void BBC::SetEdep(double aedep)
{
  edep=aedep; /// in MeV
}

void BBC::SetHit(std::vector<BBCParticle*> abbchit)
{
  bbchit=abbchit;
}

double BBC::GetEdep()
{
  return edep;
}

std::vector<BBCParticle*> BBC::GetHit()
{
  return bbchit;
}
