/*
 *  $Id: DmpRdcDataManager.cc, 2014-04-06 15:59:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"

//#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"
#include "DmpRdcDataManager.h"

//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :gInDataStream(0),
  //fEvtRaw(0)
{
  std::cout<<"Setting DmpRdcDataManager"<<std::endl;
  //fEvtRaw = new DmpEventRaw();
  fPgkID += "Rdc_V1.0_";
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::InputData(const std::string &dataName){
  gInDataStream.open(dataName.c_str(),std::ios::in|std::ios::binary);
  fInDataName = dataName;
  if(not gInDataStream.good()){
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    gInDataStream.close();
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
void DmpRdcDataManager::Initialize(){
  //fEvtRaw->GetEventHeader()->Initialize();
}

//-------------------------------------------------------------------
#ifdef DmpDebug
#include <iostream>
#endif
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
  //fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::FillEvent(){
  //fEvtRaw->GetEventHeader()->GenerateTriggerStatus();
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  //delete fEvtRaw;
  std::cout<<"Delete DmpRdcDataManager"<<std::endl;
}

//-------------------------------------------------------------------
DmpRdcDataManager *gDataMgr = DmpRdcDataManager::GetInstance();


