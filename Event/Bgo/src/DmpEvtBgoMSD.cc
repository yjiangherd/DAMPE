/*
 *  $Id: DmpEvtBgoMSD.cc, 2014-04-05 14:34:15 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtBgoMSD.h"
#include "DmpDetectorBgo.h"

ClassImp(DmpEvtBgoMSD)

//------------------------------------------------------------------------------
DmpEvtBgoMSD::DmpEvtBgoMSD()
 :fSDID(0),
  fEnergy(0),
  fUsedSide(0),
  PMT0(0),
  PMT1(0)
{
  for (int i=0;i<3;++i) fPosition[i]=0;
  PMT0 = new DmpEvtBgoPMT();
  PMT1 = new DmpEvtBgoPMT();
}

//------------------------------------------------------------------------------
DmpEvtBgoMSD::~DmpEvtBgoMSD(){
  delete PMT0;
  delete PMT1;
}

//-------------------------------------------------------------------
void DmpEvtBgoMSD::Reset(){

}

//------------------------------------------------------------------------------
void DmpEvtBgoMSD::PrintHit() const{
}

//-------------------------------------------------------------------
void DmpEvtBgoMSD::AddG4Hit(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}

//-------------------------------------------------------------------
void DmpEvtBgoMSD::SetSignal(const int &id,const short &v){
  static short dyID = 0;
  dyID = id%10;
  if(id/10 == 0){ // PMT0
    if(dyID == 5){
      PMT0->fAdcDy5 = v;
    }else if(dyID == 2){
      PMT0->fAdcDy2 = v;
    }else{
      PMT0->fAdcDy8 = v;
    }
  }else{    // PMT1
    if(dyID == 5){
      PMT1->fAdcDy5 = v;
    }else if(dyID == 2){
      PMT1->fAdcDy2 = v;
    }else{
      PMT1->fAdcDy8 = v;
    }
  }
}

