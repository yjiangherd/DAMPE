
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtPsd.hh"

DmpEvtPsdRaw::DmpEvtPsdRaw()
{}

DmpEvtPsdRaw::~DmpEvtPsdRaw(){
}

Bool_t DmpEvtPsdRaw::BookBranch(TTree* tree, Bool_t read, TString pre){
  BookBranchSubDet(tree, read,pre);
  BookBranchPsdRaw(tree, read, pre);
  return true;
}

void DmpEvtPsdRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fADC = 0;
}

void DmpEvtPsdRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}

void DmpEvtPsdRaw::BookBranchPsdRaw(TTree* tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_ACD",&fADC);
  } else {
    tree->Branch(pre+"_ACD",&fADC,"fADC/F");
  }
}


