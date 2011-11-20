//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4Mag_EqRhs.hh,v 1.8 2003/11/05 12:54:13 japost Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
//
// class G4Mag_EqRhs
//
// Class description:
//
// The "standard" equation of motion of a particle in a pure magnetic field.

// History:
// - Created. J.Apostolakis, January 13th 1997
// --------------------------------------------------------------------

//#ifndef G4_MAG_EQRHS_DEF
//#define G4_MAG_EQRHS_DEF

#include "G4Types.hh"
//#include "G4SIunits.hh"
//#include "G4EquationOfMotion.hh"

class G4MagneticField;

class G4Mag_EqRhs //: public G4EquationOfMotion
{
  public: // with description

      G4Mag_EqRhs( G4MagneticField *magField );
      virtual ~G4Mag_EqRhs();
       //~ // Constructor and destructor. No actions.

     //~ virtual void EvaluateRhsGivenB( const  G4double y[],
                                     //~ const  G4double B[3],
                                            //~ G4double dydx[] ) const = 0;
       //~ // Given the value of the  field "B", this function 
       //~ // calculates the value of the derivative dydx.
       //~ // This is the _only_ function a subclass must define.
       //~ // The other two functions use Rhs_givenB.

     inline G4double FCof() const;

      virtual void SetChargeMomentumMass( G4double particleCharge, // in e+ units
                                          G4double MomentumXc,
                                          G4double mass);
     
  private:

     G4double fCof_val;

     //~ static const G4double fUnitConstant;     // Set in G4Mag_EqRhs.cc 
                                              //~ // to 0.299792458
       //~ // Coefficient in the Lorentz motion equation (Lorentz force), if the
       //~ //  magnetic field B is in Tesla, the particle charge in units of the 
       //~ //  elementary (positron?) charge, the momentum P in MeV/c, and the
       //~ //  space coordinates and path along the trajectory in mm .
};

inline
G4double G4Mag_EqRhs::FCof() const
{
	return fCof_val;
}

//~ #endif /* G4_MAG_EQRHS_DEF */
