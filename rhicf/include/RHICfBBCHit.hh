#ifndef RHICFBBCHIT_H
#define RHICFBBCHIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

#include "BBCParticle.hpp"

class RHICfBBCHit: public G4VHit
{
public:
  RHICfBBCHit();
  RHICfBBCHit(G4int aside, G4int abbc, G4double aEdep, std::vector<BBCParticle*> aParticle);
  virtual ~RHICfBBCHit();

  /// Copy constructor & assignment operator
  RHICfBBCHit(const RHICfBBCHit& right);
  const RHICfBBCHit& operator=(const RHICfBBCHit& right);
  G4int operator==(const RHICfBBCHit& right) const;
 
  /// new/delete operators
  void* operator new(size_t);
  void operator delete(void* aHit);
  
  /// set/get functions
  void SetSide(G4int aside) {side=aside;};
  G4int GetSide() {return side;};
  void SetBBC(G4int abbc) {bbc=abbc;};
  G4int GetBBC() {return bbc;};
  void SetEdep(G4double aEdep) {Edep=aEdep;};
  G4double GetEdep() const {return Edep;};
  void SetHit(std::vector<BBCParticle*> aParticle) {Particle=aParticle;};
  std::vector<BBCParticle*> GetHit() const {return Particle;};

  /// Methods
  virtual void Draw();
  virtual void Print();

private:
  G4int side;
  G4int bbc;
  G4double Edep;
  std::vector<BBCParticle*> Particle;
};

/////////
/// inline functions
inline RHICfBBCHit::RHICfBBCHit(const RHICfBBCHit& right): G4VHit()
{
  side=right.side;
  bbc=right.bbc;
  Edep=right.Edep;
  Particle=right.Particle;
}

inline const RHICfBBCHit& RHICfBBCHit::operator=(const RHICfBBCHit& right)
{
  side=right.side;
  bbc=right.bbc;
  Edep=right.Edep;
  Particle=right.Particle;

  return *this;
}

inline G4int RHICfBBCHit::operator==(const RHICfBBCHit& right) const 
{
   return (this==&right) ? 1 : 0; 
}

typedef G4THitsCollection<RHICfBBCHit> BBCHitsCollection;
extern G4Allocator<RHICfBBCHit> RHICfBBCHitAllocator; 

inline void* RHICfBBCHit::operator new(size_t)
{
  void* aHit = (void*)RHICfBBCHitAllocator.MallocSingle();
  return aHit;
}

inline void RHICfBBCHit::operator delete(void* aHit)
{
  RHICfBBCHitAllocator.FreeSingle((RHICfBBCHit*) aHit);
}

#endif
