
#include <iostream>

#include "DmpDcdParameterNud.hh"
#include "DmpEvtNud.hh"
#include "DmpRdcNud.hh"

using namespace std;
using namespace DmpDcdParameter::Nud;

DmpRdcNud::DmpRdcNud()
  :fEvt(0)
{
  fEvt = new DmpEvtNudRaw();
  fTree = fEvt->GetTree("Nud");
}

DmpRdcNud::~DmpRdcNud(){
  delete fEvt;
}

Bool_t DmpRdcNud::SetConnector(){
  cout<<"\n\tSetup Nud connector"<<endl;
/*
  Int_t FEEID, ChannelID;
  Short_t LayerID, BarID, SideID, DyID;
  Int_t ChannelNbOneLayerOneSide = (kBarNb+kRefBarNb)*kDyNb;
  string tmp;
  for(Int_t p=0;p<kPlaneNb;++p){
    char fileName[20];
    sprintf(fileName,"Plane_%d.infor",p);
    ifstream mapFile(fConnectorPath+"Nud/"+fileName);
    if (!mapFile.good()) {cout<<"\tfailed"<<endl; return false;}
    for(Int_t layerID=0;layerID<2;++layerID){
      for(Int_t sideID=0;sideID<2;++sideID){
        getline(mapFile,tmp);   mapFile>>LayerID;
        getline(mapFile,tmp);   mapFile>>SideID;
        getline(mapFile,tmp);   mapFile>>FEEID;
        getline(mapFile,tmp);
        for(Int_t c=0;c<ChannelNbOneLayerOneSide;++c){
          mapFile>>BarID; mapFile>>DyID; mapFile>>ChannelID;
          Short_t array[4] = {LayerID,BarID,SideID,DyID};
          Connector.insert(make_pair(FEEID*1000+ChannelID,array));       //FEEID*1000 + ChannelID as key, since ChannelNbOneLayerOneSide = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
        }
      }
    }
    mapFile.close();
  }
*/
  cout<<"\tsuccess"<<endl;
  return true;
}

//  need real data to implement this part
Bool_t DmpRdcNud::Conversion(ifstream *HexData){
  cout<<"\t\t\tEvent Conversion:\tNud"<<endl;
  Short_t tmp=0;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    cout<<"\t\t\t\t----> 0xeb wrong"<<endl;
    return false;
  }
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    cout<<"\t\t\t\t----> 0xeb wrong"<<endl;
    return false;
  }
  for (Short_t i=0;i<fDataLength-2;++i)
  HexData->read((char*)(&tmp),1);
  
  return true;
}

