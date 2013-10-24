/*=============================================================================
#       FileName :          dmpRdc.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-03   08:46:33
#
#------------------------------------------------------------------------------
#       Description  :
#           Refer to ./Reade.md
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-16   16:56:51
=============================================================================*/

#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpRdcHeader.hh"
#include "DmpRdcPsd.hh"
#include "DmpRdcStk.hh"
#include "DmpRdcBgo.hh"
#include "DmpRdcNud.hh"

using namespace std;

int main(int argc, char* argv[]){
  TString inFileName = "DmpRdcInput.infor";
  if (argc == 2) inFileName = argv[1];

  ifstream* BatchInfor = 0;
  if ( inFileName.Contains(".infor") && inFileName.Contains("DmpRdcInput") ) {
    BatchInfor = new ifstream (inFileName,ios::in);
  } else {
    cout<<"Usage:\n\t1. dmpRdc\n\t2. dmpRdc /path/DmpRdcInput.infor"<<endl;
  }

  if (!BatchInfor->good()) {
    cout<<"\n\t---->Error: there's not a file named "<<inFileName<<endl;
    return 0;
  }

  string note, dataName, inDataPath,outDataPath;
  for (Short_t i=0;i<4;++i) {
    getline(*BatchInfor,note);    // reserved 4 lines for note
  }
  getline(*BatchInfor,inDataPath);
  getline(*BatchInfor,note);      // reserved 1 line for note
  getline(*BatchInfor,outDataPath);
  getline(*BatchInfor,note);     // reserved 1 line for note
  *BatchInfor>>dataName;         // get the first dataName

  DmpRdcManager* RdcMan = DmpRdcManager::GetInstance();
  if ( !RdcMan->GetPsd()->SetConnector()) return 0;
  if ( !RdcMan->GetStk()->SetConnector()) return 0;
  if ( !RdcMan->GetBgo()->SetConnector()) return 0;
  if ( !RdcMan->GetNud()->SetConnector()) return 0;

  RdcMan->SetInDataPath(inDataPath);
  RdcMan->SetOutDataPath(outDataPath);

  while (dataName != "END") {
    RdcMan->SetDataName(dataName);
    ifstream* InData = new ifstream((TString)inDataPath+(TString)dataName,ios::in|ios::binary);
    if (!InData->good()) {
      cout<<"\n\t---->Warning: open "<<inDataPath+dataName<<" failed"<<endl;
      *BatchInfor>>dataName;
      continue;
    } else {
      cout<<"\n\t---->Reading "<<inDataPath+dataName<<endl;
    }

    if ( ! RdcMan->BookTree() ) {
      *BatchInfor>>dataName;
      continue;
    }
    if ( ! RdcMan->BookBranch() ) {
      *BatchInfor>>dataName;
      continue;
    }

    //loop of event package. set the order of suv-detector as the order of FEE in InData
    for (Long64_t nEvt=0;!InData->eof();++nEvt) {
//Long64_t EvtID = RdcMan->GetHeader()->GetPackageID();
//if (EvtID == 20) break;

      if (! RdcMan->GetHeader()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetNud()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetPsd()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetStk()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetBgo()->Conversion(InData)) {
        continue;
      }

      RdcMan->FillAnEvent();
    }

    RdcMan->SaveRootFile();
    InData->close();
    *BatchInfor>>dataName;
  }
  BatchInfor->close();
  RdcMan->Clear();
  cout<<"\n\t---->End of Raw Data Conversion"<<endl;

}


