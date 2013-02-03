#include "trialwavefunction.h"

TrialWaveFunction::TrialWaveFunction(vec varparam, int nP, int nD)
{
    variationalParameters = varparam;
    nDimensions = nD;
    nParticles = nP;
}
