#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String name);
    ~MySensitiveDetector();

private:
    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist);
    G4int fLastEventID = -1;
};

#endif