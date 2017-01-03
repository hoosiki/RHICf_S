#include "BBCParticle.hpp"

BBCParticle::BBCParticle()
{
  pdgcode=0;
  momentum=TLorentzVector();
}

BBCParticle::~BBCParticle()
{;}

void BBCParticle::SetPDGCode(int apdgcode)
{ pdgcode=apdgcode; }
void BBCParticle::SetMomentum(TLorentzVector amomentum)
{ momentum=amomentum; }

int BBCParticle::GetPDGCode()
{ return pdgcode; }
TLorentzVector BBCParticle::GetMomentum()
{ return momentum; }
