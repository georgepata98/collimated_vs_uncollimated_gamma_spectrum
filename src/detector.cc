#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    if(track->GetParentID() != 0) return false; // doar fotonul primar, nu si cei secundari
    if(track->GetDefinition() != G4Gamma::GammaDefinition()) return false; // doar gamme
    if(!aStep->IsFirstStepInVolume()) return false; // doar primul step in volum
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(eventID == fLastEventID) return false;
    fLastEventID = eventID;

    G4double KE = track->GetKineticEnergy();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0, KE / keV);
    analysisManager->FillNtupleDColumn(0, 0, KE / keV);
    analysisManager->AddNtupleRow(0);

    return true;
}