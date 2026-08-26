#include "physics.hh"

MyPhysicsList::MyPhysicsList()
:G4VModularPhysicsList(),
fEm(nullptr)
{
    SetVerboseLevel(0);

    /* G4EmParameters *param = G4EmParameters::Instance();
    param->SetFluo(true);
    param->SetAuger(true);
    param->SetPixe(true); */

    fEm = new G4EmStandardPhysics_option4(0);
    RegisterPhysics(fEm);
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::SetCuts()
{
    G4VUserPhysicsList::SetCuts();
    defaultCutValue = 0.1*mm;
    SetCutsWithDefault();

    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV, 100*GeV);
}