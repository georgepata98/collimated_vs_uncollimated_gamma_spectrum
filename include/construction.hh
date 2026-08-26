#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Cons.hh"

#include "G4SubtractionSolid.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
    G4Box *sDetector, *sPereteSus, *sPereteJos, *sPereteFata, *sPereteSpate, *sPereteDreapta, *sPereteStanga;
    G4LogicalVolume *lDetector, *lPereteSus, *lPereteJos, *lPereteFata, *lPereteSpate, *lPereteDreapta, *lPereteStanga, *lSubtraction, *lCollimator;
    G4VPhysicalVolume *pDetector, *pPereteSus, *pPereteJos, *pPereteSpate, *pPereteDreapta, *pPereteStanga, *pSubtraction;
    G4Cons *sCollimator;
    G4SubtractionSolid *sSubtraction;

    virtual void ConstructSDandField();

    // Se modifica in true sau false functie daca vrem sau nu colimator
    bool collimatedGeom = false;
};

#endif
