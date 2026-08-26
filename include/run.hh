#ifndef RUN_HH
#define RUN_HH

#include "G4SystemOfUnits.hh"
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4AccValue.hh"
#include "G4AccumulableManager.hh"

#include <iostream>
#include <string>

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction() override;

    virtual void BeginOfRunAction(const G4Run *run) override;
    virtual void EndOfRunAction(const G4Run *run) override;
};

#endif