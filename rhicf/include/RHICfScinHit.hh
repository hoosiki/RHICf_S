#ifndef RHICFSCINHIT_H
#define RHICFSCINHIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

class RHICfScinHit: public G4VHit
{
public:
  RHICfScinHit();
  RHICfScinHit(G4int ascin, G4double aedep);
  virtual ~RHICfScinHit();

  /// Copy constructor & assignment operator
  RHICfScinHit(const RHICfScinHit& right);
  const RHICfScinHit& operator=(const RHICfScinHit& right);
  G4int operator==(const RHICfScinHit& right) const;
  
  /// new/delete operators
  void* operator new(size_t);
  void operator delete(void* aHit);
  
  /// set/get functions
  void SetScin(G4int ascin) {scin=ascin;}
  G4int GetScin() const {return scin;}
  void SetEdep(G4double aedep) {edep=aedep;}
  G4double GetEdep() const {return edep;}

  /// Methods
  virtual void Draw();
  virtual void Print();

private:
  G4int scin;
  G4double edep;
};

/////////
/// inline functions
inline RHICfScinHit::RHICfScinHit(const RHICfScinHit& right): G4VHit()
{
  scin=right.scin;
  edep=right.edep;
}

inline const RHICfScinHit& RHICfScinHit::operator=(const RHICfScinHit& right)
{
  scin=right.scin;
  edep=right.edep;
  return *this;
}

inline G4int RHICfScinHit::operator==(const RHICfScinHit& right) const 
{
   return (this==&right) ? 1 : 0; 
}

typedef G4THitsCollection<RHICfScinHit> ScinHitsCollection;
extern G4Allocator<RHICfScinHit> RHICfScinHitAllocator; 

inline void* RHICfScinHit::operator new(size_t)
{
  void* aHit = (void*)RHICfScinHitAllocator.MallocSingle();
  return aHit;
}

inline void RHICfScinHit::operator delete(void* aHit)
{
  RHICfScinHitAllocator.FreeSingle((RHICfScinHit*) aHit);
}

#endif
