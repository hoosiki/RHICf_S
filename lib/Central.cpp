#include "Central.hpp"

Central::Central()
{
  id=0;
  motherid=0;
  pdgcode=0;
  momentum=TLorentzVector();
  position1=TVector3();
  position2=TVector3();
}

Central::~Central()
{;}

void Central::SetID(int aid)
{ id=aid; }
void Central::SetMotherID(int amotherid)
{ motherid=amotherid; }
void Central::SetPDGcode(int apdgcode)
{ pdgcode=apdgcode; }
void Central::SetMomentum(TLorentzVector amomentum)
{ momentum=amomentum; }
void Central::SetPosition1(TVector3 aposition1)
{ position1=aposition1; }
void Central::SetPosition2(TVector3 aposition2)
{ position2=aposition2; }
void Central::SetBoundary(bool aisboundary)
{ isboundary=aisboundary; }

int Central::GetID()
{ return id; }
int Central::GetMotherID()
{ return motherid; }
int Central::GetPDGcode()
{ return pdgcode; }
TLorentzVector Central::GetMomentum()
{ return momentum; }
TVector3 Central::GetPosition1()
{ return position1; }
TVector3 Central::GetPosition2()
{ return position2; }
bool Central::isBoundary()
{ return isboundary; }
