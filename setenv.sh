#!/bin/bash

export HEPMC_ROOT=_SET_HEPMC_DIRECTORY_
export HEPMC_INCLUDE=${HEPMC_ROOT}/include
export HEPMC_LIBRARY=${HEPMC_ROOT}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HEPMC_LIBRARY}

export BOOST_ROOT=_SET_BOOST_DIRECTORY_
export BOOST_INCLUDE=${BOOST_ROOT}/include
export BOOST_LIBRARY=${BOOST_ROOT}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${BOOST_LIBRARY}

export PYTHIA8_ROOT=_SET_PYTHIA8_DIRECTORY_
export PYTHIA8_INCLUDE=${PYTHIA8_ROOT}/include
export PYTHIA8_LIBRARY=${PYTHIA8_ROOT}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PYTHIA8_LIBRARY}

export RHICF_TOP=_SET_THIS_DIRECTORY_
export RHICF_LIB=${RHICF_TOP}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${RHICF_LIB}