#ifndef RHICFTRACKINFORMATION_H
#define RHICFTRACKINFORMATION_H 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class RHICfTrackInformation : public G4VUserTrackInformation 
{
public:
  RHICfTrackInformation();
  RHICfTrackInformation(const G4Track* aTrack);
  RHICfTrackInformation(const RHICfTrackInformation* aTrackInfo);
  virtual ~RHICfTrackInformation();
   
  inline void *operator new(size_t);
  inline void operator delete(void *aTrackInfo);

  RHICfTrackInformation& operator =(const RHICfTrackInformation& right);
  
  void SetSourceTrackInformation(const G4Track* aTrack);
  virtual void Print() const;

private:
  // Information of the primary track at the primary vertex
  G4int                 fOriginalTrackID;  // Track ID of primary particle
  G4ParticleDefinition* fParticleDefinition;
  G4ThreeVector         fOriginalPosition;
  G4ThreeVector         fOriginalMomentum;
  G4double              fOriginalEnergy;
  G4double              fOriginalTime;

  G4int                 fSourceTrackID;
  G4ParticleDefinition* fSourceDefinition;
  G4ThreeVector         fSourcePosition;
  G4ThreeVector         fSourceMomentum;
  G4double              fSourceEnergy;
  G4double              fSourceTime;
};

extern G4ThreadLocal G4Allocator<RHICfTrackInformation> * aTrackInformationAllocator;

inline void* RHICfTrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<RHICfTrackInformation>;
  return (void*)aTrackInformationAllocator->MallocSingle();
}

inline void RHICfTrackInformation::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator->FreeSingle((RHICfTrackInformation*)aTrackInfo);}

#endif

