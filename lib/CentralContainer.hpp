#ifndef CENTRALCONTAINER_HPP
#define CENTRALCONTAINER_HPP

#include <vector>

#include "TObject.h"

#include "Central.hpp"

class CentralContainer: public TObject
{
public:
  CentralContainer();
  ~CentralContainer();
  void Reset();
  void Push_back(Central* acentral);
  std::vector<Central*> GetContainer();

  void SetProcess(int aprocess) {process=aprocess;};
  int GetProcess() {return process;};

private:
  std::vector<Central*> centralCont;
  int process;

  ClassDef(CentralContainer, 1)
};

#endif
