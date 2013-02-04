#ifndef VMCSOLVER_H
#define VMCSOLVER_H

#include "trialwavefunction.h"
#include "hydrogenlike.h"

#include <armadillo>

using namespace arma;
using namespace std;

class VMCSolver
{
public:
    VMCSolver();
    void run();

protected:
    double kineticEnergy(const mat &r);
    double localEnergy(const mat &r);

    TrialWaveFunction* waveFunction;

    int nDimensions;
    int charge;
    double stepLength;
    int nParticles;
    double h;
    double h2;
    long idum;

    vec variationalParameters;

    int nCycles;

    mat rOld;
    mat rNew;
};

#endif // VMCSOLVER_H
