#ifndef BBCPARTICLE_HPP
#define BBCPARTICLE_HPP

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"

class BBCParticle: public TObject
{
public:
  BBCParticle();
  ~BBCParticle();

  void SetPDGCode(int apdgcode);
  void SetMomentum(TLorentzVector amomentum);

  int GetPDGCode();
  TLorentzVector GetMomentum();

private:
  int pdgcode;
  TLorentzVector momentum;


  ClassDef(BBCParticle, 1)  
};

#endif
