#include "run.hh"

MyRunAction::MyRunAction()
: G4UserRunAction()
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);

    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetNtupleMerging(true);
    
    // Mai jos se modifica nr. bini, E_min si E_max din spectru:
    analysisManager->CreateH1("Eg", "Gamma spectra", 1000, 0, 1010);  // nbins, x_min, x_max
    analysisManager->CreateNtuple("Eg", "Gamma spectra");
    analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
    G4int runID = run->GetRunID();

    G4AccumulableManager *accMan = G4AccumulableManager::Instance();
    accMan->Reset();
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    auto analysisManager = G4AnalysisManager::Instance();

    G4String fileName = ("spectrum_Run" + std::to_string(runID) + ".root").c_str();
    analysisManager->OpenFile(fileName);
}

void MyRunAction::EndOfRunAction(const G4Run *run)
{
    G4int runID = run->GetRunID();

    G4int nOfEvents = run->GetNumberOfEvent();
    if(nOfEvents == 0) return;

    G4AccumulableManager *accMan = G4AccumulableManager::Instance();
    accMan->Merge();

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
