/*
 *  $Id: DmpRdcAlgStk.cc, 2014-05-28 13:15:04 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtHeader.h"
#include "DmpEvtRdcStkLadder.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpDataBuffer.h"

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::InitializeStk(){
  if(fCNCTPathStk == "NO"){
    DmpLogWarning<<"No set connector:\tStk"<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"Setting connector:\tStk"<<DmpLogEndl;
  }
  // setup connector
// *
// *  TODO: set method?
// *
  fCNCTDoneStk = true;
  fStkLadderSet = new TClonesArray("DmpEvtRdcStkLadder",190); // TODO ,size ??
  if(not gDataBuffer->RegisterObject("Event/Rdc/Stk",fStkLadderSet)){
    fIniStatus = false;
    return;
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventStk(){
  fStkLadderSet->Delete();
  DmpLogDebug<<"[Stk] from "<<fFile.tellg();
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0, data=0;
  static unsigned short data2=0;
//-------------------------------------------------------------------
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::AppendSignalStk(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

