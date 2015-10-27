/* Generated by Together
 * modified by: M. Babai
 */
#include "E105GeoSlit.h"
#include "E105Slit.h"
#include "E105SlitPar.h"
#include "E105GeoPassivePar.h"

#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairGeoRootBuilder.h"
#include "FairGeoNode.h"
#include "FairGeoMedia.h"
#include "FairRuntimeDb.h"
#include "TObjArray.h"
#include "TGeoPcon.h"
#include "TGeoVolume.h"
#include "TGeoMatrix.h"
#include "TGeoManager.h"
#include "TGeoCompositeShape.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoBBox.h"
#include "TGeoTrd1.h"
#include "TGeoPgon.h"
#include "TGeoTube.h"
#include "TGeoSphere.h"
#include "TGeoArb8.h"
#include "TGeoCone.h"
#include "TGeoTorus.h"
#include "TGeoTrd2.h"
#include "TGeoBoolNode.h"
#include "TGeoCompositeShape.h"
#include "TGeoManager.h"
#include "FairRun.h"
#include "TVector3.h"

E105Slit::~E105Slit()
{
}

E105Slit::E105Slit()
  : FairModule("E105Slit", "")
{
}

E105Slit::E105Slit(const char* name, const char* title)
  : FairModule(name ,title)
{
}

void E105Slit::ConstructGeometry()
{
  TGeoElementTable *table = gGeoManager->GetElementTable();

  Double_t density =        0.;
  Double_t a       =        0.;
  Double_t z       =        0.;
  Int_t numed      =        0 ;
  // Specific Material definition
  // --  Material: Vacuum
  TGeoMedium * pMedVac=NULL;
  if (gGeoManager->GetMedium("Vacuum") ){
    pMedVac=gGeoManager->GetMedium("Vacuum");
   }else{
    a = 0.;
    z = 0.;
    density = 0.;
    TGeoMaterial *mat = new TGeoMaterial("Vacuum", a, z, density);
    numed   = 1;  // medium number
    Double_t par[8];
    par[0]  = 0.000000; // isvol
    par[1]  = 1.000000; // ifield
    par[2]  = 1.000000; // fieldm
    par[3]  = 0.000000; // tmaxfd
    par[4]  = 0.000000; // stemax
    par[5]  = 0.000000; // deemax
    par[6]  = 0.000100; // epsil
    par[7]  = 0.000000; // stmin
    pMedVac = new TGeoMedium("Vacuum", numed,mat, par);
   }
  // --  Material: Tantalum
  TGeoMedium * pMedTa=NULL;
  if (gGeoManager->GetMedium("Tantalum") ){
    pMedTa=gGeoManager->GetMedium("Tantalum");
   }else{
    TGeoElement *el   = table->FindElement("Tungsten");
    density = 16.69;
    TGeoMaterial *mat = new TGeoMaterial("Tantalum", el, density);
    numed   = 2;  // medium number
    Double_t par[8];
    par[0]  = 0.000000; // isvol
    par[1]  = 1.000000; // ifield
    par[2]  = 1.000000; // fieldm
    par[3]  = 0.000000; // tmaxfd
    par[4]  = 0.000000; // stemax
    par[5]  = 0.000000; // deemax
    par[6]  = 0.000100; // epsil
    par[7]  = 0.000000; // stmin
    pMedTa = new TGeoMedium("Tantalum", numed,mat, par);
   }

  // virtual slit geometrical descriptions
  Double_t slitX = 3.60;   //[cm]
  Double_t slity = 5.92;   //[cm]
  Double_t slitz  = 0.2;   //[cm]
  
  // Geometry description
  ///////////
  TGeoVolume *pAWorld =  gGeoManager->GetTopVolume();
  
  // Main Slit Envelope (not to be seen or detected)
  TGeoShape *slitVirBox = new TGeoBBox("slitVirBox",slitX/2, slity/2, slitz/2);
  TGeoVolume* slit = new TGeoVolume("slitVirBox", slitVirBox, pMedVac);
  slit->SetVisibility(0);

  // global Positioning Slit
  Double_t s2target = 3.0;      // cm   //----------> Par to DB
  Double_t slitShift = -0.75;   // cm   //----------> Par to DB
  
  Double_t det2Rotation = 80.5; // deg
  TVector3 vec = TVector3(slitShift,0,s2target);
  vec.RotateY(det2Rotation*TMath::Pi()/180.);
  Double_t tx = vec.X(); // (cm)
  Double_t ty = vec.Y(); // (cm)
  Double_t tz = vec.Z(); // (cm)
  
  TGeoRotation *rot0 = new TGeoRotation();
  rot0->RotateX(0.);
  rot0->RotateY(det2Rotation);
  rot0->RotateZ(0.);
  TGeoCombiTrans *t0 = new TGeoCombiTrans(vec.X(),vec.Y(),vec.Z(),rot0);

  pAWorld->AddNode(slit, 0, t0);

  //_________________________________________
  // this part is modified in order to store the parameters via fair
  // base.
  // Update Fair parameters   sets.
  // Get run and runtime database
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();

  E105SlitPar* pars = 0;
  pars = (E105SlitPar*)(rtdb->getContainer("E105SlitPar"));

  if(pars != 0) {
    std::cout << "\n<INFO> THE CONTAINER IS FOUND\n";
    pars->SetS2Target(s2target);
    pars->SetSlitShift(slitShift);
    pars->setChanged();
    pars->setInputVersion(fRun->GetRunId(), 1);
    std::cout << "\n";
  }
  //_________________________________________
  // create the slits
  ConstructDetails(slit);
}

void E105Slit::ConstructDetails(TGeoVolume* slit)
{
  // medium 
  ////////////
  TGeoMedium *pMedTa = gGeoManager->GetMedium("Tantalum");

  // Geometry description
  // main bulk
  ///////// 
  Double_t slitx1 = 3.20;   //[cm]
  Double_t slitx2 = 3.60;   //[cm]
  Double_t slitx  = 3.50;   //[cm]
  Double_t slity  = 5.92;   //[cm]
  Double_t slitz  = 0.2;    //[cm]

  TGeoShape *sTrd1 = new TGeoTrd1("sTrd1",slitx1/2, slitx2/2, slity/2, slitz/2);
  TGeoShape *sBox  = new TGeoBBox("sBox" ,slitx/2, slity, slitz);
  TGeoIntersection* slitInt = new TGeoIntersection(sTrd1,sBox);
  TGeoShape *slitBulk = new TGeoCompositeShape("slitBulk", slitInt);

  // boolean parts 
  // slits
  //////////////////////////////
  Double_t dx,dy,dz;
  Double_t rmin,rmax;
  Double_t thx,thy,thz,phx,phy,phz;
  dx=0.1; // [cm]
  dy=1.3; // [cm]
  dz=slitz;
  TGeoShape *B1 = new TGeoBBox("B1",dx/2.,dy/2.,dz);
  dx=0.2; // [cm]
  dy=1.2; // [cm]
  TGeoShape *B2 = new TGeoBBox("B2",dx/2.,dy/2.,dz);
  rmin=0;   // [cm]
  rmax=0.1/2.; // [cm]
  TGeoShape *B3 = new TGeoTube("B3",rmin,rmax,dz);
  rmax=0.2/2.; // [cm]
  TGeoShape *B4 = new TGeoTube("B4",rmin,rmax,dz);
  // #1 subtraction type: TGeoCompositeShape
  thx=-0.75; 
  thy=0.0;
  thz=0;
  TGeoTranslation *tr1 = new TGeoTranslation("tr1",thx,thy,thz);
  TGeoSubtraction *sb1 = new TGeoSubtraction(slitBulk,B1,0,tr1);
  TGeoShape *sb1_shape = new TGeoCompositeShape("sb1_shape", sb1);
  // #2 subtraction type: TGeoCompositeShape
  thx=0.75; 
  thy=0.0;
  thz=0;
  TGeoTranslation *tr2 = new TGeoTranslation("tr2",thx,thy,thz);
  TGeoSubtraction *sb2 = new TGeoSubtraction(sb1_shape,B2,0,tr2);
  TGeoShape *sb2_shape = new TGeoCompositeShape("sb2_shape", sb2);
  // #3 subtraction type: TGeoCompositeShape
  thx=-0.75; 
  thy=-1.3/2.;
  thz=0;
  TGeoTranslation *tr3 = new TGeoTranslation("tr3",thx,thy,thz);
  TGeoSubtraction *sb3 = new TGeoSubtraction(sb2_shape,B3,0,tr3);
  TGeoShape *sb3_shape = new TGeoCompositeShape("sb3_shape", sb3);
  // #4 subtraction type: TGeoCompositeShape
  thx=-0.75; 
  thy=1.3/2.;
  thz=0;
  TGeoTranslation *tr4 = new TGeoTranslation("tr4",thx,thy,thz);
  TGeoSubtraction *sb4 = new TGeoSubtraction(sb3_shape,B3,0,tr4);
  TGeoShape *sb4_shape = new TGeoCompositeShape("sb4_shape", sb4);
  // #5 subtraction type: TGeoCompositeShape
  thx=0.75; 
  thy=-1.3/2.;
  thz=0;
  TGeoTranslation *tr5 = new TGeoTranslation("tr5",thx,thy,thz);
  TGeoSubtraction *sb5 = new TGeoSubtraction(sb4_shape,B4,0,tr5);
  TGeoShape *sb5_shape = new TGeoCompositeShape("sb5_shape", sb5);
  // #6 subtraction type: TGeoCompositeShape
  thx=0.75; 
  thy=1.3/2.;
  thz=0;
  TGeoTranslation *tr6 = new TGeoTranslation("tr6",thx,thy,thz);
  TGeoSubtraction *sb6 = new TGeoSubtraction(sb5_shape,B4,0,tr6);
  TGeoShape *sb6_shape = new TGeoCompositeShape("sb6_shape", sb6);
  // make the composit volume
  TGeoVolume *comp = new TGeoVolume("COMP",sb6_shape,pMedTa);
  TGeoCombiTrans *t0 = new TGeoCombiTrans("");

  // add to the virtual slit frame
  ///////
  slit->AddNode(comp, 0, t0);
}
ClassImp(E105Slit)
