RHICFLIBNAME = libRHICfEvent.so

CXX      = g++
CXXFLAGS = -fPIC -shared

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)
ROOTGLIBS  = $(shell root-config --glibs)

SRCS  = $(shell ls *.cpp)
HEADS = $(shell ls *.hpp)

DICTNAME = dict
LINKDEF_H  = LinkDef.h

CXXFLAGS += $(ROOTCFLAGS)

all: $(RHICFLIBNAME)

$(RHICFLIBNAME): $(DICTNAME).cc $(SRCS)
	$(CXX) $(CXXFLAGS) $(DICTNAME).cc $(SRCS) $(ROOTLIBS) -o $(RHICFLIBNAME)

$(DICTNAME): $(HEADS) $(SRCS)
	rootcint -f $(DICTNAME).cc -c $(HEADS) $(LINKDEF_H)

clean:
	rm -f *~ $(RHICFLIBNAME)

cleanall:
	rm -f *~ $(RHICFLIBNAME) $(DICTNAME).*