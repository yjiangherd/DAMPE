/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-05-19 12:32:53 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#include "DmpRdcAlgHeader.h"
#include "DmpEvtRdcHeader.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader::DmpRdcAlgHeader()
 :DmpVAlg("Header/Rdc/2014"),
  fFile(0),
  fEvtHeader(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
// *
  fFile = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->InFileStream();
  fEvtHeader = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->GetEventHeader();
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::ProcessThisEvent(){
  static bool firstIn = true;
  if(firstIn){
    LogDebug<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
//-------------------------------------------------------------------
  static short tmp=0;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
// *
// *  TODO: trigger first byte means??
// *
  fFile->read((char*)(&tmp),1);      // this needed
  fFile->read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(tmp);
  fFile->read((char*)(&tmp),1);      // Datalength
  fFile->read((char*)(&tmp),1);      // Datalength
  for (std::size_t index=0;index<8;++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  if(not firstIn){
    LogDebug<<" to "<<fFile->tellg()<<std::endl;
    firstIn = true;
  }
  return true;
}


