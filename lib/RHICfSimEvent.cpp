#include "RHICfSimEvent.hpp"

RHICfSimEvent::RHICfSimEvent()
{
  central=NULL;
  forward=NULL;
  mc=NULL;
  reco=NULL;
  zdc=NULL;
  bbc=NULL;
  romanpot=NULL;
}

RHICfSimEvent::~RHICfSimEvent()
{
}

void RHICfSimEvent::SetCentral(CentralContainer *acentral)
{ central=acentral; }
void RHICfSimEvent::SetForward(ForwardContainer *aforward)
{ forward=aforward; }
void RHICfSimEvent::SetMC(MCDataContainer *amc)
{ mc=amc; }
void RHICfSimEvent::SetReco(RecoDataContainer *areco)
{ reco=areco; }
void RHICfSimEvent::SetZDC(ZDCContainer *azdc)
{ zdc=azdc; }
void RHICfSimEvent::SetBBC(BBCContainer *abbc)
{ bbc=abbc; }
void RHICfSimEvent::SetRomanPot(RomanPotContainer *aromanpot)
{ romanpot=aromanpot; }


ForwardContainer* RHICfSimEvent::GetForward()
{ return forward; }
CentralContainer* RHICfSimEvent::GetCentral()
{ return central; }
MCDataContainer* RHICfSimEvent::GetMC()
{ return mc; }
RecoDataContainer* RHICfSimEvent::GetReco()
{ return reco; }
ZDCContainer* RHICfSimEvent::GetZDC()
{ return zdc; }
BBCContainer* RHICfSimEvent::GetBBC()
{ return bbc; }
RomanPotContainer* RHICfSimEvent::GetRomanPot()
{ return romanpot; }
