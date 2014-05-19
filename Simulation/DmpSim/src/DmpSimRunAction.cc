/*
 *  $Id: DmpSimRunAction.cc, 2014-04-16 11:15:19 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include <time.h>
#include "CLHEP/Random/Random.h"

#include "DmpSimRunAction.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpCore.h"
#include "DmpLog.h"

//-------------------------------------------------------------------
DmpSimRunAction::DmpSimRunAction()
 :fDataMgr(0)
{
}

//-------------------------------------------------------------------
DmpSimRunAction::~DmpSimRunAction(){
}

//-------------------------------------------------------------------
void DmpSimRunAction::BeginOfRunAction(const G4Run *aRun){
  LogInfor<<"Run ID = "<<aRun->GetRunID()<<std::endl;
  fDataMgr->BookBranch(); 
// *  TODO: engine not works...
  //CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time((time_t*)NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  //CLHEP::HepRandom::showEngineStatus(); 

#ifdef G4VIS_USE
  if(G4VVisManager::GetConcreteInstance()){
    G4UImanager *uiManager = G4UImanager::GetUIpointer();
    uiManager->ApplyCommand("vis/clear/view");
  }
#endif
}

//-------------------------------------------------------------------
void DmpSimRunAction::EndOfRunAction(const G4Run* aRun){
  fDataMgr->SaveOutput();
  /***
  if ( fSaveRndm ) { 
    G4int runNumber = run->GetRunID();
    std::ostringstream fileName;
    fileName << "run" << runNumber << "end.rndm";
    CLHEP::HepRandom::saveEngineStatus(fileName.str().c_str()); 
    CLHEP::HepRandom::showEngineStatus();
  }
  ***/
}

//-------------------------------------------------------------------
bool DmpSimRunAction::Initialize(){
  fDataMgr = (DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr");
  return fDataMgr;
}


