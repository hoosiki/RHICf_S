#include "RomanPot.hpp"

RomanPot::RomanPot()
{
  pdgcode=0;
  momentum=TLorentzVector();
  position1=TVector3();
  position2=TVector3();
}

RomanPot::~RomanPot()
{;}

void RomanPot::SetPDGcode(int apdgcode)
{ pdgcode=apdgcode; }
void RomanPot::SetMomentum(TLorentzVector amomentum)
{ momentum=amomentum; }
void RomanPot::SetPosition1(TVector3 aposition1)
{ position1=aposition1; }
void RomanPot::SetPosition2(TVector3 aposition2)
{ position2=aposition2; }

int RomanPot::GetPDGcode()
{ return pdgcode; }
TLorentzVector RomanPot::GetMomentum()
{ return momentum; }
TVector3 RomanPot::GetPosition1()
{ return position1; }
TVector3 RomanPot::GetPosition2()
{ return position2; }
