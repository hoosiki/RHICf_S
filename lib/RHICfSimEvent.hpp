#ifndef RHICFSIMEVENT_HPP
#define RHICFSIMEVENT_HPP

#include "TObject.h"

#include "CentralContainer.hpp"
#include "ForwardContainer.hpp"
#include "MCDataContainer.hpp"
#include "RecoDataContainer.hpp"
#include "ZDCContainer.hpp"
#include "BBCContainer.hpp"
#include "RomanPotContainer.hpp"

class RHICfSimEvent: public TObject
{
public:
  RHICfSimEvent();
  ~RHICfSimEvent();

  void SetForward(ForwardContainer *aforward);
  void SetCentral(CentralContainer *acentral);
  void SetMC(MCDataContainer *amc);
  void SetReco(RecoDataContainer *areco);
  void SetZDC(ZDCContainer *azdc);
  void SetBBC(BBCContainer *abbc);
  void SetRomanPot(RomanPotContainer *aromanpot);

  ForwardContainer* GetForward();
  CentralContainer* GetCentral();
  MCDataContainer* GetMC();
  RecoDataContainer* GetReco();
  ZDCContainer* GetZDC();
  BBCContainer* GetBBC();
  RomanPotContainer* GetRomanPot();

private:
  ForwardContainer *forward;
  CentralContainer *central;
  MCDataContainer *mc;
  RecoDataContainer *reco;
  ZDCContainer *zdc;
  BBCContainer *bbc;
  RomanPotContainer *romanpot;

  ClassDef(RHICfSimEvent, 1)
};

#endif
