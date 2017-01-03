#ifndef CENTRAL_HPP
#define CENTRAL_HPP

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"

class Central: public TObject
{
public:
  Central();
  ~Central();

  void SetID(int aid);
  void SetMotherID(int amotherid);
  void SetPDGcode(int apdgcode);
  void SetMomentum(TLorentzVector amomentum);
  void SetPosition1(TVector3 aposition1);
  void SetPosition2(TVector3 aposition1);
  void SetBoundary(bool aboundary);

  int GetID();
  int GetMotherID();
  int GetPDGcode();
  TLorentzVector GetMomentum();
  TVector3 GetPosition1();
  TVector3 GetPosition2();
  bool isBoundary();

private:
  int id;
  int motherid;
  int pdgcode;
  TLorentzVector momentum;
  TVector3 position1;
  TVector3 position2;
  bool isboundary;

  ClassDef(Central, 1)
};

#endif
