#ifndef HYDROGENLIKE_H
#define HYDROGENLIKE_H

#include "trialwavefunction.h"

#include <armadillo>
using namespace arma;

class HydrogenLike : public TrialWaveFunction
{
public:
    HydrogenLike(vec &, int, int);
    virtual double f(mat &r);
    virtual double laplacian(mat &r, double h);

protected:
    double alpha;
};

#endif // HYDROGENLIKE_H
