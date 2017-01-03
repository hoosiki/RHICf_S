#include <iostream>

#include "ForwardContainer.hpp"

ForwardContainer::ForwardContainer()
{
}

ForwardContainer::~ForwardContainer()
{
}

void ForwardContainer::Push_back(Forward* aforward)
{
  forwardCont.push_back(aforward);
}

void ForwardContainer::Reset()
{
  for(unsigned int i=0; i<forwardCont.size(); i++) 
    delete forwardCont[i];
  forwardCont.clear();
}

std::vector<Forward*> ForwardContainer::GetContainer()
{
  return forwardCont;
}
