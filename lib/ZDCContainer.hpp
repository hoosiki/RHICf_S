#ifndef ZDCCONTAINER_HPP
#define ZDCCONTAINER_HPP

#include <vector>

#include "TObject.h"

#include "RHICfParam.hpp"

class ZDCContainer: public TObject
{
public:
  ZDCContainer();
  virtual ~ZDCContainer();
  virtual void Reset();

  int GetMaxModule();
  double GetSumModule();

  void SetZDC(int azdc, double aedep);
  void SetNphoton(int azdc, int anphoton);
  void SetSMD(int axy, int asmd, double aedep);
  void SetScin(int ascin, double aedep);

  std::vector<double> GetZDC();
  std::vector<int> GetNphoton();
  std::vector<std::vector<double> > GetSMD();
  std::vector<double> GetScin();

private:
  std::vector<double> zdc;
  std::vector<int> nphoton;
  std::vector<std::vector<double> > smd;
  std::vector<double> scin;

  ClassDef(ZDCContainer, 1)
};

#endif
