#ifndef RHICFPARAM_HPP
#define RHICFPARAM_HPP 1

#include "Flag.hpp"

static const int ntower=2;
static const int nplate=16;
static const int nbelt=4;
static const int nxy=2;
static const int nbar[ntower]={20,40};
static const int nunused=4;

static const int nzdc=3;
static const int nsmd[nxy]={8,7};
static const int nscin=2;

static const int nside=2;
static const int nbbc=36;

static const int nstation=4;
static const double pstation[nstation]={15.8e3,17.1e3,55.5e3,58.5e3};

enum FLAGS
  {
    bNONE          = 0,
    bGENERATE      = (1<<0),
    bTRANSPORT     = (1<<1),
    bRESPONSE_ARM1 = (1<<2),
    bRESPONSE_ZDC  = (1<<3),
    bBEAMTEST      = (1<<4),

    bRESPONSE      = bRESPONSE_ARM1 | bRESPONSE_ZDC,
    bFULL          = bGENERATE | bTRANSPORT | bRESPONSE_ARM1 | bRESPONSE_ZDC,

    bBEAMTEST_ARM1 = bBEAMTEST | bRESPONSE_ARM1,
    bBEAMTEST_ZDC  = bBEAMTEST | bRESPONSE_ZDC,
    bBEAMTEST_ALL  = bBEAMTEST | bRESPONSE,

    bALL = bGENERATE | bTRANSPORT | bRESPONSE | bBEAMTEST
  };

#endif
