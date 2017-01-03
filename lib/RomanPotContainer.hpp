#ifndef ROMANPOTCONTAINER_HPP
#define ROMANPOTCONTAINER_HPP

#include <vector>

#include "TObject.h"

#include "RomanPot.hpp"

class RomanPotContainer: public TObject
{
public:
  RomanPotContainer();
  ~RomanPotContainer();
  void Reset();
  void Push_back(RomanPot* aromanpot);
  std::vector<RomanPot*> GetContainer();

private:
  std::vector<RomanPot*> romanpotCont;

  ClassDef(RomanPotContainer, 1)
};

#endif
