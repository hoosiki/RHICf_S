# $Id: GNUmakefile 2015.08.25 stak $
# --------------------------------------------------------------
# GNUmakefile
# --------------------------------------------------------------

name := rhicf
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = /opt/software/geant4.10.01.p02/share/Geant4-10.1.2/geant4make
endif

.PHONY: all
all: lib bin
ifndef XERCESCROOT	
	@echo XERCESCROOT not defined!
endif

include $(G4INSTALL)/config/binmake.gmk

# Enable ROOT output option
CPPFLAGS += -D__OUTPUT_ROOTFILE__

# Add compile flags and extra libs for ROOT output
CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS = $(shell $(ROOTSYS)/bin/root-config --glibs)
EXTRALIBS += $(ROOTLIBS)

clean:
	rm -f *~ src/*~ include/*~

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*
