/** E105SiLiMapPar.h
 ** @author M.Al-Turany
 ** @since 30.01.2007
 ** @version 1.0
 **
 ** Parameter set field maps.
 **/


#ifndef E105SILIMAPPAR_H
#define E105SILIMAPPAR_H 1


#include "FairField.h"
#include "FairParGenericSet.h"


class FairParamList;


class E105SiLiMapPar : public FairParGenericSet
{

  public:


    /** Standard constructor  **/
    E105SiLiMapPar(const char* name, const char* title, const char* context);

    /** default constructor  **/
    E105SiLiMapPar();

    /** Destructor **/
    ~E105SiLiMapPar();



    /** Accessors **/
    Int_t    GetType()      const { return fType; }
    Double_t GetXmin()      const { return fXmin; }
    Double_t GetXmax()      const { return fXmax; }
    Double_t GetYmin()      const { return fYmin; }
    Double_t GetYmax()      const { return fYmax; }
    Double_t GetZmin()      const { return fZmin; }
    Double_t GetZmax()      const { return fZmax; }
    void MapName(TString& name) { name = fMapName; }
    Double_t GetPositionX() const { return fPosX; }
    Double_t GetPositionY() const { return fPosY; }
    Double_t GetPositionZ() const { return fPosZ; }
    Double_t GetScale()     const { return fScale; }


  protected:

    /** Field type
     ** 0 = constant field
     ** 1 = field map
     ** 2 = field map sym2 (symmetries in x and y)
     ** 3 = field map sym3 (symmetries in x, y and z)
     **/
    Int_t fType;


    /** Field limits in case of constant field **/
    Double_t fXmin, fXmax;
    Double_t fYmin, fYmax;
    Double_t fZmin, fZmax;



    /** Field map name in case of field map **/
    TString fMapName;


    /** Field centre position for field map **/
    Double_t fPosX, fPosY, fPosZ;


    /** Scaling factor for field map **/
    Double_t fScale;


    ClassDef(E105SiLiMapPar,1);

};


#endif
