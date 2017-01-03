#ifndef FLAG_HPP
#define FLAG_HPP

#include "TObject.h"

class Flag: public TObject
{
public:
  Flag();
  ~Flag();
  bool equal(unsigned char f) const;
  bool check(unsigned char f) const;
  void set(unsigned char f);
  void reset(unsigned char f);

private:
  unsigned char mFlag;

  ClassDef(Flag, 1)
};
#endif
