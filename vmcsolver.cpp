#include "vmcsolver.h"
#include "lib.h"

using namespace arma;
using namespace std;

VMCSolver::VMCSolver()
{
    stepLength = 1.0;
    nParticles = 2;
    nDimensions = 3;
    idum = -1;
    charge = 2;
    h = 0.001;
    h2 = 1.0/h/h;
    variationalParameters = zeros(1);
    variationalParameters(0) = 1;
    waveFunction = new HydrogenLike(variationalParameters, nParticles, nDimensions);
}

void VMCSolver::run()
{   
    rOld = zeros<mat>(nParticles, nDimensions);
    rNew = zeros<mat>(nParticles, nDimensions);

    double deltaE;

    // initial trial positions
    for(int i = 0; i < nParticles; i++) {
        for(int j = 0; j < nDimensions; j++) {
            rOld(i,j) = stepLength * (ran2(&idum) - 0.5);
        }
    }
    rNew = rOld;

    cout << rOld<<"  " << localEnergy(rOld)<< endl;
}


/**
 * @brief VMCSolver::localEnergy
 * @param r matrix of electron positions
 * @return local energy of the system, as defined in report
 */
double VMCSolver::localEnergy(const mat &r)
{
    double kinetic_energy = 0.5*waveFunction->laplacian(r, h)/waveFunction->f(r);
    cout << "Kinetic energy: " << kinetic_energy << endl;

    double potential_energy = 0;

    // Contribution from nucleus
    double rSingleParticle = 0;
    for (int i = 0; i<nParticles; i++) {
        rSingleParticle = 0;
        for (int j = 0; j<nParticles; j++) {
            rSingleParticle += r(i,j)*r(i,j);
        }
        potential_energy -= charge/sqrt(rSingleParticle);
    }

    // Electron-electron contribution
    double r12 = 0;
    for (int i = 0; i<nParticles; i++) {
        for (int j = i+1; i<nParticles; i++) {
            r12 = 0;
            for (int k = 0; k<nDimensions; k++) {
                r12 += (r(i,k) - r(j,k))*(r(i,k)-r(j,k));
            }
            potential_energy += 1.0/sqrt(r12);
        }
    }

    // Summing and returning local energy
    return potential_energy+kinetic_energy;

}


