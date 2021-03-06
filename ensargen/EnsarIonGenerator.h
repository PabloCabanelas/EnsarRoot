// -----------------------------------------------------------------------
// -----               EnsarIonGenerator header file                 -----
// -----                  Based on FairIonGenerator                  -----
// -----               Created 14/09/12  by P. Cabanelas             -----
// -----------------------------------------------------------------------

/** Include beam spot size **/

#ifndef ENSARIONGENERATOR_H
#define ENSARIONGENERATOR_H


#include "FairGenerator.h"
#include "FairIon.h"

#include <iostream>

class FairPrimaryGenerator;

class EnsarIonGenerator : public FairGenerator
{

 public:

  /** Default constructor **/
  EnsarIonGenerator();


  /** Constructor with ion name    
    ** For the generation of ions with pre-defined FairIon 
   ** By default, the  excitation energy is zero. This can be changed with the
   ** respective modifiers.
   **@param ionName  Ion name
   **@param mult      Number of ions per event
   **@param px,py,pz  Momentum components [GeV] per nucleon!
   **@param vx,vy,vz  Vertex coordinates [cm]
   **/
  EnsarIonGenerator(const Char_t* ionName, Int_t mult, Double_t px, 
		  Double_t py, Double_t pz);


  /** Default constructor 
   ** For the generation of ions with atomic number z and mass number a.
   ** By default, the mass equals a times the proton mass and the 
   ** excitation energy is zero. This can be changed with the
   ** respective modifiers.
   **@param z         Atomic number
   **@param a         Atomic mass
   **@param q         Electric charge [e]
   **@param mult      Number of ions per event
   **@param px,py,pz  Momentum components [GeV] per nucleon!
   **@param vx,vy,vz  Vertex coordinates [cm]
   **/
  EnsarIonGenerator(Int_t z, Int_t a, Int_t q, Int_t mult, Double_t px, 
		  Double_t py, Double_t pz);


  /** Destructor **/
  virtual ~EnsarIonGenerator();


  /** Modifiers **/
  void SetCharge(Int_t charge){fQ=charge;}
  void SetExcitationEnergy(Double_t eExc);
  void SetMass(Double_t mass);

  void SetSpotRadius   (Double32_t r=0, Double32_t z=0, Double32_t off=0) {
    fR=r; fz=z; fOffset=off; fBeamSpotIsSet=kTRUE;}


  /** Method ReadEvent 
   ** Generates <mult> of the specified ions and hands hem to the
   ** FairPrimaryGenerator. 
   **/
  virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);


private:

  static Int_t fgNIon;      //! Number of the instance of this class
  Int_t    fMult;           // Multiplicity per event
  Double_t fPx, fPy, fPz;   // Momentum components [GeV] per nucleon
  Double32_t fR, fz, fOffset;  // beam Spot radius [cm], z source, y source
  Double_t fVx, fVy, fVz;   // Vertex coordinates [cm]
  FairIon   *fIon;          // Pointer to the FairIon to be generated
  Int_t    fQ;		    // Electric charge [e]

  Bool_t fBeamSpotIsSet;    // True if point beamspot is set
    
  ClassDef(EnsarIonGenerator,1)

}; 


#endif
   

