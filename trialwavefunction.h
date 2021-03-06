#ifndef TRIALWAVEFUNCTION_H
#define TRIALWAVEFUNCTION_H

#include <armadillo>
using namespace arma;

class TrialWaveFunction
{
public:
    TrialWaveFunction(vec, int, int);
    virtual double f(const mat &r) = 0;
    virtual double laplacian(const mat &r, double h) = 0;

protected:
    vec variationalParameters;
    int nDimensions;
    int nParticles;
};

#endif // TRIALWAVEFUNCTION_H
