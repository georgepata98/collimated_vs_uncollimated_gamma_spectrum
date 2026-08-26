#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    // Materiale

    G4NistManager *nist = G4NistManager::Instance();

    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *PbMat = nist->FindOrBuildMaterial("G4_Pb");

    // Geometrii

    G4Box *solidWorld = new G4Box("solidWorld", 30*cm, 30*cm, 30*cm);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0);

    if(collimatedGeom == true)
    {
        sPereteSus = new G4Box("sPereteSus", 20*cm, 5*cm, 20*cm);
        lPereteSus = new G4LogicalVolume(sPereteSus, PbMat, "lPereteSus");

        sPereteJos = new G4Box("sPereteJos", 20*cm, 5*cm, 20*cm);
        lPereteJos = new G4LogicalVolume(sPereteJos, PbMat, "lPereteJos");

        sPereteFata = new G4Box("sPereteFata", 20*cm, 10*cm, 5.*cm);
        lPereteFata = new G4LogicalVolume(sPereteFata, PbMat, "lPereteFata");

        sPereteSpate = new G4Box("sPereteSpate", 20*cm, 10*cm, 5*cm);
        lPereteSpate = new G4LogicalVolume(sPereteSpate, PbMat, "lPereteSpate");

        sPereteDreapta = new G4Box("sPereteDreapta", 5*cm, 10*cm, 10*cm);
        lPereteDreapta = new G4LogicalVolume(sPereteDreapta, PbMat, "lPereteDreapta");

        sPereteStanga = new G4Box("sPereteStanga", 5*cm, 10*cm, 10*cm);
        lPereteStanga = new G4LogicalVolume(sPereteStanga, PbMat, "lPereteStanga");

        sCollimator = new G4Cons("sCollimator", 0*cm, 3*cm, 0*cm, 6*cm, 5.*cm, 0*deg, 360*deg);
        lCollimator = new G4LogicalVolume(sCollimator, worldMat, "lCollimator");

        // Peretele din fata din care s-a taiat conul colimator
        sSubtraction = new G4SubtractionSolid("sSubtraction", sPereteFata, sCollimator, 0, G4ThreeVector(0, 0, 0));
        lSubtraction = new G4LogicalVolume(sSubtraction, PbMat, "lSubtraction");

        // Pozitionarea in World Volume

        pPereteSus = new G4PVPlacement(0, G4ThreeVector(0, 15*cm, 0), lPereteSus, "pPereteSus", logicWorld, false, 0);
        pPereteJos = new G4PVPlacement(0, G4ThreeVector(0, -15*cm, 0), lPereteJos, "pPereteJos", logicWorld, false, 0);
        pSubtraction = new G4PVPlacement(0, G4ThreeVector(0, 0, 15*cm), lSubtraction, "pSubtraction", logicWorld, false, 0);
        pPereteSpate = new G4PVPlacement(0, G4ThreeVector(0, 0, -15*cm), lPereteSpate, "pPereteSpate", logicWorld, false, 0);
        pPereteDreapta = new G4PVPlacement(0, G4ThreeVector(15*cm, 0, 0), lPereteDreapta, "pPereteDreapta", logicWorld, false, 0);
        pPereteStanga = new G4PVPlacement(0, G4ThreeVector(-15*cm, 0, 0), lPereteStanga, "pPereteStanga", logicWorld, false, 0);
    }

    // Detectorul virtual subtire, din aer, amplasat in fata colimatorului
    sDetector = new G4Box("sDetector", 10*cm, 10*cm, .5*mm);
    lDetector = new G4LogicalVolume(sDetector, worldMat, "lDetector");
    pDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 23*cm), lDetector, "pDetector", logicWorld, false, 0);

    // Vizualizare

    G4VisAttributes *red = new G4VisAttributes(G4Colour::Red());
    G4VisAttributes *blue = new G4VisAttributes(G4Colour::Blue());
    red->SetVisibility(true);
    blue->SetVisibility(true);
    // red->SetForceSolid(true);
    // blue->SetForceSolid(true);
    lDetector->SetVisAttributes(red);

    if(collimatedGeom == true)
    {
        lPereteSus->SetVisAttributes(blue);
        lPereteJos->SetVisAttributes(blue);
        lSubtraction->SetVisAttributes(blue);
        lPereteSpate->SetVisAttributes(blue);
        lPereteDreapta->SetVisAttributes(blue);
        lPereteStanga->SetVisAttributes(blue);
    }
    
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
    lDetector->SetSensitiveDetector(sensDet);
}
