/*
 *  $Id: DmpSimNudSD.cc, 2014-05-09 11:07:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimNudSD.h"
#include "DmpEvtMCNudMSD.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpCore.h"
#include "DmpLog.h"

//-------------------------------------------------------------------
DmpSimNudSD::DmpSimNudSD(G4String name)
 :G4VSensitiveDetector(name)
{
}

//-------------------------------------------------------------------
DmpSimNudSD::~DmpSimNudSD(){
}

//-------------------------------------------------------------------
void DmpSimNudSD::Initialize(G4HCofThisEvent*){
  fMSDSet = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kNud);
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimNudSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string blockName = theTouchable->GetVolume()->GetName();
  blockName.assign(blockName.end()-1,blockName.end());        // get ID
  short blockID = boost::lexical_cast<short>(blockName);
  DmpEvtMCNudMSD *aMSD = 0;
  for(short i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtMCNudMSD*)fMSDSet->At(i))->GetSDID() == blockID){
      aMSD = (DmpEvtMCNudMSD*)fMSDSet->At(i);
      break;
    }
  }
  if(aMSD == 0){
    LogDebug<<"\thit a new block: "<<blockID<<std::endl;
    aMSD = (DmpEvtMCNudMSD*)fMSDSet->New(fMSDSet->GetEntriesFast());
    aMSD->SetSDID(blockID);
  }
  aMSD->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,aStep->GetPreStepPoint()->GetGlobalTime()/ns);
  return true;
}

//-------------------------------------------------------------------
void DmpSimNudSD::EndOfEvent(G4HCofThisEvent* HCE){
}


