#ifndef VMCSOLVER_H
#define VMCSOLVER_H

#include "trialwavefunction.h"
#include "hydrogenlike.h"
#include <libconfig.h++>
#include <armadillo>
#include "lib.h"


using namespace arma;
using namespace std;
using namespace libconfig;

class VMCSolver
{
public:
    VMCSolver(Config &_cfg);
    void runMCWithMetropolis();

protected:
    double kineticEnergy(const mat &r);
    double localEnergy(const mat &r);

    double waveFunctionOld;
    double waveFunctionNew;

    double deltaE;
    double energySum;
    double energySquaredSum;

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

    Config* cfg;
};

#endif // VMCSOLVER_H
