#ifndef RHICFFORWARDHIT_H
#define RHICFFORWARDHIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

class RHICfForwardHit: public G4VHit
{
public:
  RHICfForwardHit();
  virtual ~RHICfForwardHit();

  /// Copy constructor & assignment operator
  RHICfForwardHit(const RHICfForwardHit& right);
  const RHICfForwardHit& operator=(const RHICfForwardHit& right);
  G4int operator==(const RHICfForwardHit& right) const;
 
  /// new/delete operators
  void* operator new(size_t);
  void operator delete(void* aHit);
  
  /// set/get functions
  void SetMotherID(G4int aMotherID) {MotherID=aMotherID;};
  G4int GetMotherID() const {return MotherID;};
  void SetPDGCode(G4int aPDGCode) {PDGCode=aPDGCode;};
  G4int GetPDGCode() const {return PDGCode;};
  void SetEnergy(G4double aEnergy) {Energy=aEnergy;};
  G4double GetEnergy() const {return Energy;};
  void SetEkinetic(G4double aEkinetic) {Ekinetic=aEkinetic;};
  G4double GetEkinetic() const {return Ekinetic;};
  void SetPosition(G4ThreeVector aPosition) {Position=aPosition;};
  G4ThreeVector GetPosition() const {return Position;};
  void SetDirection(G4ThreeVector aDirection) {Direction=aDirection;};
  G4ThreeVector GetDirection() const {return Direction;};
  void SetisBackground(G4bool aisBackground) {isBackground=aisBackground;};
  G4bool GetisBackground() const {return isBackground;};
  
  /// Methods
  virtual void Draw();
  virtual void Print();

private:
  G4int MotherID;
  G4int PDGCode;
  G4double Energy;
  G4double Ekinetic;
  G4ThreeVector Position;
  G4ThreeVector Direction;
  G4bool isBackground;
};

/////////
/// inline functions
inline RHICfForwardHit::RHICfForwardHit(const RHICfForwardHit& right): G4VHit()
{
  MotherID=right.MotherID;
  PDGCode=right.PDGCode;
  Energy=right.Energy;
  Ekinetic=right.Ekinetic;
  Position=right.Position;
  Direction=right.Direction;
  isBackground=right.isBackground;
}

inline const RHICfForwardHit& RHICfForwardHit::operator=(const RHICfForwardHit& right)
{
  MotherID=right.MotherID;
  PDGCode=right.PDGCode;
  Energy=right.Energy;
  Ekinetic=right.Ekinetic;
  Position=right.Position;
  Direction=right.Direction;
  isBackground=right.isBackground;
  return *this;
}

inline G4int RHICfForwardHit::operator==(const RHICfForwardHit& right) const 
{
   return (this==&right) ? 1 : 0; 
}

typedef G4THitsCollection<RHICfForwardHit> ForwardHitsCollection;
extern G4Allocator<RHICfForwardHit> RHICfForwardHitAllocator; 

inline void* RHICfForwardHit::operator new(size_t)
{
  void* aHit = (void*)RHICfForwardHitAllocator.MallocSingle();
  return aHit;
}

inline void RHICfForwardHit::operator delete(void* aHit)
{
  RHICfForwardHitAllocator.FreeSingle((RHICfForwardHit*) aHit);
}

#endif
