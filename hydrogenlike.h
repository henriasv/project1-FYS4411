#ifndef HYDROGENLIKE_H
#define HYDROGENLIKE_H

#include "trialwavefunction.h"

#include <armadillo>
using namespace arma;

class HydrogenLike : public TrialWaveFunction
{
public:
    HydrogenLike(vec &, int, int);
    virtual double f(const mat &r);
    virtual double laplacian(const mat &r, double h);

protected:
    double alpha;
};

#endif // HYDROGENLIKE_H
