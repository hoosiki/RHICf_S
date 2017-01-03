#ifndef BBCCONTAINER_HPP
#define BBCCONTAINER_HPP

#include <vector>

#include "TObject.h"

#include "BBC.hpp"
#include "RHICfParam.hpp"

class BBCContainer: public TObject
{
public:
  BBCContainer();
  ~BBCContainer();
  void Reset();
  void SetBBC(int aside, int aid, BBC* abbc);
  std::vector< std::vector<BBC*> > GetContainer();

private:
  std::vector< std::vector<BBC*> > bbcCont;

  ClassDef(BBCContainer, 1)
};

#endif
