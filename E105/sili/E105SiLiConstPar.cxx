#include "E105SiLiConstPar.h"
//#include "FairConstField.h"
#include "FairParamList.h"
// ------   Constructor   --------------------------------------------------
E105SiLiConstPar::E105SiLiConstPar(const char* name, const char* title, const char* context)
  : E105SiLiMapPar(name, title, context), fBx(0), fBy(0), fBz(0)
{
  fType=0;
}

E105SiLiConstPar::E105SiLiConstPar()
  : E105SiLiMapPar(), fBx(0), fBy(0), fBz(0)
{
  fType=0;
}

E105SiLiConstPar::~E105SiLiConstPar() { }

void E105SiLiConstPar::putParams(FairParamList* list)
{
  if ( ! list ) { return; }

  list->add("Field Type", fType);

  list->add("Field min x", fXmin);
  list->add("Field max x", fXmax);
  list->add("Field min y", fYmin);
  list->add("Field max y", fYmax);
  list->add("Field min z", fZmin);
  list->add("Field max z", fZmax);
  list->add("Field Bx", fBx);
  list->add("Field By", fBy);
  list->add("Field Bz", fBz);

}



Bool_t E105SiLiConstPar::getParams(FairParamList* list)
{
  if ( ! list ) { return kFALSE; }
  if ( ! list->fill("Field Type", &fType) ) { return kFALSE; }
  if ( ! list->fill("Field min x", &fXmin) ) { return kFALSE; }
  if ( ! list->fill("Field max x", &fXmax) ) { return kFALSE; }
  if ( ! list->fill("Field min y", &fYmin) ) { return kFALSE; }
  if ( ! list->fill("Field max y", &fYmax) ) { return kFALSE; }
  if ( ! list->fill("Field min z", &fZmin) ) { return kFALSE; }
  if ( ! list->fill("Field max z", &fZmax) ) { return kFALSE; }
  if ( ! list->fill("Field Bx", &fBx) ) { return kFALSE; }
  if ( ! list->fill("Field By", &fBy) ) { return kFALSE; }
  if ( ! list->fill("Field Bz", &fBz) ) { return kFALSE; }
  return kTRUE;
}
// void E105SiLiConstPar:: SetParameters(FairField* field)
// {
//   FairConstField* fieldConst = (FairConstField*) field;
//   fBx = fieldConst->GetBx();
//   fBy = fieldConst->GetBy();
//   fBz = fieldConst->GetBz();
//   fXmin = fieldConst->GetXmin();
//   fXmax = fieldConst->GetXmax();
//   fYmin = fieldConst->GetYmin();
//   fYmax = fieldConst->GetYmax();
//   fZmin = fieldConst->GetZmin();
//   fZmax = fieldConst->GetZmax();
//   fMapName = "";
//   fPosX = fPosY = fPosZ = fScale = 0.;
//   fType = fieldConst->GetType();
// }



ClassImp(E105SiLiConstPar)

