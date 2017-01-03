#include "Flag.hpp"
#include "RHICfParam.hpp"

Flag::Flag(): mFlag(0)
{
}

Flag::~Flag(){}

bool Flag::equal(unsigned char f) const
{
  return (mFlag == f) ? true : false;
}

bool Flag::check(unsigned char f) const
{
  return ((mFlag & f)!=0) ? true : false;
}

void Flag::set(unsigned char f)
{
  mFlag |= f;
}

void Flag::reset(unsigned char f)
{
  mFlag &= ~f;
}
