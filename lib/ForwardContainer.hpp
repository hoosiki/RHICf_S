#ifndef FORWARDCONTAINER_HPP
#define FORWARDCONTAINER_HPP

#include <vector>

#include "TObject.h"

#include "Forward.hpp"

class ForwardContainer: public TObject
{
public:
  ForwardContainer();
  ~ForwardContainer();
  void Reset();
  void Push_back(Forward* aforward);
  std::vector<Forward*> GetContainer();

private:
  std::vector<Forward*> forwardCont;

  ClassDef(ForwardContainer, 1)
};

#endif
