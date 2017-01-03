#ifndef RHICFDETECTORCONSTRUCTION_H
#define RHICFDETECTORCONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"
#include "globals.hh"

#include "RHICfParam.hpp"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4OpticalSurface;

class RHICfGSOplateSD;

class RHICfDetectorConstruction : public G4VUserDetectorConstruction
  {
  public:
    RHICfDetectorConstruction();
    ~RHICfDetectorConstruction();

    G4VPhysicalVolume* Construct();
    void SetOpticalProperties();
    void SetTables(std::string atables);
    void SetGeometry(std::string afgeometry, std::string afdetector, Flag aflag);
    Flag GetDetectorFlag();
    void SetCuts(G4double aetacut, G4double aecut, bool aopposite);

  private:
    G4String fReadFile;
    G4String ftables;
    G4GDMLParser parser;
    Flag flag;

    G4double etacut;
    G4double ecut;
    bool opposite;

    G4OpticalSurface* fOpsurface1;
    G4OpticalSurface* fOpsurface2;
  };

#endif
