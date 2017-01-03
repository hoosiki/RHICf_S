#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4ParticleTypes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

#include "RHICfCentralHit.hh"

/// allocator
G4Allocator<RHICfCentralHit> RHICfCentralHitAllocator;

//////////
/// Constructor and Destructor
RHICfCentralHit::RHICfCentralHit()
{
  TrackID=0;
  MotherID=0;
  PDGCode=0;
  Energy=0;
  Ekinetic=0;
  Position1=G4ThreeVector();
  Position2=G4ThreeVector();
  Direction=G4ThreeVector();
  isBoundary=false;
}

RHICfCentralHit::~RHICfCentralHit()
{
}

//////////
/// Draw
void RHICfCentralHit::Draw()
{
}

//////////
/// Print
void RHICfCentralHit::Print()
{
  G4cout << std::setw(9) << "  TrackID: " << TrackID
	 << " Energy: " << G4BestUnit(Energy,"Energy")
	 << G4endl;
}
