#ifndef BBC_HPP
#define BBC_HPP

#include <vector>

#include "TObject.h"

#include "BBCParticle.hpp"
#include "RHICfParam.hpp"

class BBC: public TObject
{
public:
  BBC();
  BBC(const BBC& obj);
  ~BBC();
  void Reset();
  void SetEdep(double aedep);
  //  void Push_back(BBCParticle* abbcparticle);
  void SetHit(std::vector<BBCParticle*> abbchit);
  double GetEdep();
  std::vector<BBCParticle*> GetHit();

private:
  double edep;
  std::vector<BBCParticle*> bbchit;

  ClassDef(BBC, 1)
};

#endif
