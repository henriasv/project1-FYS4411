#include "hydrogenlike.h"

HydrogenLike::HydrogenLike(vec &varparam, int nParticles, int nDimensions) : TrialWaveFunction(varparam, nParticles, nDimensions)
{
    alpha = variationalParameters[0];
}

double HydrogenLike::f(mat &r)
{
    double argument = 0;
    for (int i = 0; i<nParticles; i++) {
        double rSingleParticle = 0;
        for (int j = 0; j<nDimensions; j++) {
            rSingleParticle += r(i, j) * r(i, j);
        }
        argument += sqrt(rSingleParticle);
    }
    return exp(-argument*alpha);
}


/**
 * @brief HydrogenLike::laplacian
 * @param r
 * @return Sum of the laplacians for all the particles.
 */
double HydrogenLike::laplacian(mat &r, double h)
{

    mat rPlus = zeros<mat>(nParticles, nDimensions);
    mat rMinus = zeros<mat>(nParticles, nDimensions);

    rPlus = rMinus = r;

    double waveFunctionMinus = 0;
    double waveFunctionPlus = 0;

    double waveFunctionCurrent = f(r);

    double value = 0;
    for(int i = 0; i < nParticles; i++) {
        for(int j = 0; j < nDimensions; j++) {
            rPlus(i,j) += h;
            rMinus(i,j) -= h;
            waveFunctionMinus = f(rMinus);
            waveFunctionPlus = f(rPlus);
            value += (waveFunctionMinus + waveFunctionPlus - 2 * waveFunctionCurrent);
            rPlus(i,j) = r(i,j);
            rMinus(i,j) = r(i,j);
        }
    }
    return value/(h*h);
}


