// Extra Class for TsDNA
//
// ********************************************************************
// *                                                                  *
// * This file is part of the TOPAS-nBio extensions to the            *
// *   TOPAS Simulation Toolkit.                                      *
// * The TOPAS-nBio extensions are freely available under the license *
// *   agreement set forth at: https://topas-nbio.readthedocs.io/     *
// *                                                                  *
// ********************************************************************
//
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// and the DNA geometry given in the Geom_DNA example 
// shall cite the following Geant4-DNA collaboration publications:
// [1] NIM B 298 (2013) 47-54
// [2] Med. Phys. 37 (2010) 4692-4708
// The Geant4-DNA web site is available at http://geant4-dna.org
//
// $ID$
/// \file ChromosomeParameterisation.cc
/// \brief Implementation of the ChromosomeParameterisation class

#include <ChromosomeParameterisation.hh>

// STD
#include <fstream>

// G4
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4VPhysicalVolume.hh>

using namespace std;
using CLHEP::nanometer;
using CLHEP::degree;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ChromosomeParameterisation::ChromosomeParameterisation(const char* filename):
    G4VPVParameterisation()
{
  ifstream f(filename, ios::in);
  if (!f)
    return;

  fPositions.reserve(100);
  fRotations.reserve(100);

  while (!f.eof())
  {
    double x, y, z, rot;
    f >> x >> y >> z >> rot;
    fPositions.push_back(new G4ThreeVector(x * nanometer,
                                           y * nanometer,
                                           z * nanometer));
    fRotations.push_back(new G4RotationMatrix(0, 0, rot * degree));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ChromosomeParameterisation::~ChromosomeParameterisation()
{
  unsigned int i;
  for (i = 0; i < fPositions.size(); i++)
    delete fPositions[i];
  for (i = 0; i < fRotations.size(); i++)
    delete fRotations[i];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ChromosomeParameterisation::ComputeDimensions(
    G4Tubs& /*rosette*/,
    const G4int /*copyNo*/,
    const G4VPhysicalVolume* /*physVol*/) const
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ChromosomeParameterisation::ComputeTransformation(
    const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  // see passive vs active method to specify
  // this transformation
  physVol->SetTranslation(*fPositions[copyNo]);
  physVol->SetRotation(fRotations[copyNo]);
}
