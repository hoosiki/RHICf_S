#ifndef RHICFCENTRALHIT_H
#define RHICFCENTRALHIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

class RHICfCentralHit: public G4VHit
{
public:
  RHICfCentralHit();
  virtual ~RHICfCentralHit();

  /// Copy constructor & assignment operator
  RHICfCentralHit(const RHICfCentralHit& right);
  const RHICfCentralHit& operator=(const RHICfCentralHit& right);
  G4int operator==(const RHICfCentralHit& right) const;
 
  /// new/delete operators
  void* operator new(size_t);
  void operator delete(void* aHit);
  
  /// set/get functions
  void SetTrackID(G4int aTrackID) {TrackID=aTrackID;};
  G4int GetTrackID() const {return TrackID;};
  void SetMotherID(G4int aMotherID) {MotherID=aMotherID;};
  G4int GetMotherID() const {return MotherID;};
  void SetPDGCode(G4int aPDGCode) {PDGCode=aPDGCode;};
  G4int GetPDGCode() const {return PDGCode;};
  void SetEnergy(G4double aEnergy) {Energy=aEnergy;};
  G4double GetEnergy() const {return Energy;};
  void SetEkinetic(G4double aEkinetic) {Ekinetic=aEkinetic;};
  G4double GetEkinetic() const {return Ekinetic;};
  void SetPosition1(G4ThreeVector aPosition1) {Position1=aPosition1;};
  G4ThreeVector GetPosition1() const {return Position1;};
  void SetPosition2(G4ThreeVector aPosition2) {Position2=aPosition2;};
  G4ThreeVector GetPosition2() const {return Position2;};
  void SetDirection(G4ThreeVector aDirection) {Direction=aDirection;};
  G4ThreeVector GetDirection() const {return Direction;};
  void SetisBoundary(G4bool aisBoundary) {isBoundary=aisBoundary;};
  G4bool GetisBoundary() const {return isBoundary;};
  
  /// Methods
  virtual void Draw();
  virtual void Print();

private:
  G4int TrackID;
  G4int MotherID;
  G4int PDGCode;
  G4double Energy;
  G4double Ekinetic;
  G4ThreeVector Position1;
  G4ThreeVector Position2;
  G4ThreeVector Direction;
  G4bool isBoundary;
};

/////////
/// inline functions
inline RHICfCentralHit::RHICfCentralHit(const RHICfCentralHit& right): G4VHit()
{
  TrackID=right.TrackID;
  MotherID=right.MotherID;
  PDGCode=right.PDGCode;
  Energy=right.Energy;
  Ekinetic=right.Ekinetic;
  Position1=right.Position1;
  Position2=right.Position2;
  Direction=right.Direction;
  isBoundary=right.isBoundary;
}

inline const RHICfCentralHit& RHICfCentralHit::operator=(const RHICfCentralHit& right)
{
  TrackID=right.TrackID;
  MotherID=right.MotherID;
  PDGCode=right.PDGCode;
  Energy=right.Energy;
  Ekinetic=right.Ekinetic;
  Position1=right.Position1;
  Position2=right.Position2;
  Direction=right.Direction;
  isBoundary=right.isBoundary;
  return *this;
}

inline G4int RHICfCentralHit::operator==(const RHICfCentralHit& right) const 
{
   return (this==&right) ? 1 : 0; 
}

typedef G4THitsCollection<RHICfCentralHit> CentralHitsCollection;
extern G4Allocator<RHICfCentralHit> RHICfCentralHitAllocator; 

inline void* RHICfCentralHit::operator new(size_t)
{
  void* aHit = (void*)RHICfCentralHitAllocator.MallocSingle();
  return aHit;
}

inline void RHICfCentralHit::operator delete(void* aHit)
{
  RHICfCentralHitAllocator.FreeSingle((RHICfCentralHit*) aHit);
}

#endif
