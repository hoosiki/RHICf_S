#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4ParticleTypes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"

#include <iomanip>

#include "RHICfScinHit.hh"

/// allocator
G4Allocator<RHICfScinHit> RHICfScinHitAllocator;

//////////
/// Constructor and Destructor
RHICfScinHit::RHICfScinHit(): scin(-1), edep(0.)
{
}

RHICfScinHit::RHICfScinHit(G4int ascin, G4double aedep)
{
  scin=ascin;
  edep=aedep;
}

RHICfScinHit::~RHICfScinHit()
{
}

//////////
/// Draw
void RHICfScinHit::Draw()
{
}

//////////
/// Print
void RHICfScinHit::Print()
{
  G4cout << "Scin Hit >>> Channel:  " << scin << " "
	 << " Energy:  " << edep/CLHEP::MeV << " MeV"
	 << G4endl;
}
