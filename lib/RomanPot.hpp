#ifndef ROMANPOT_HPP
#define ROMANPOT_HPP

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"

class RomanPot: public TObject
{
public:
  RomanPot();
  ~RomanPot();

  void SetPDGcode(int apdgcode);
  void SetMomentum(TLorentzVector amomentum);
  void SetPosition1(TVector3 aposition1);
  void SetPosition2(TVector3 aposition2);

  int GetPDGcode();
  TLorentzVector GetMomentum();
  TVector3 GetPosition1();
  TVector3 GetPosition2();

private:
  int pdgcode;
  TLorentzVector momentum;
  TVector3 position1;
  TVector3 position2;

  ClassDef(RomanPot, 1)
};

#endif
