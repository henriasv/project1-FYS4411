#include "vmcsolver.h"

using namespace arma;
using namespace std;

VMCSolver::VMCSolver(Config &_cfg)
{
    cfg = &_cfg;
    // Reading settings from config file
    try {
        stepLength = cfg->lookup("settings.stepLength");
        idum = cfg->lookup("settings.idum");
        //variationalParameters = cfg->lookupValue("settings.variationalParameters");
        variationalParameters = zeros(cfg->lookup("settings.variationalParameters").getLength());
        h = cfg->lookup("settings.h");
        nCycles = cfg->lookup("settings.nCycles");
    }
    catch (const SettingNotFoundException &nfex) {
        cerr << "VMCSolver::VMCSolver(Config &_cfg):: Error reading from 'settings' object" << endl;
        exit(1);
    }

    // Reading system from config file
    try {
        nParticles = cfg->lookup("system.nParticles");
        nDimensions = cfg->lookup("system.nDimensions");
        charge = cfg->lookup("system.charge");

    }
    catch (const SettingNotFoundException &nfex) {
        cerr << "VMCSolver::VMCSolver(Config &_cfg):: Error reading from 'system' object" << endl;
    }


    h2 = 1.0/h/h;
    variationalParameters(0) = 1; cout << "Currently setting alpha to 1" << endl;

    // Creating wavefunction
    waveFunction = new HydrogenLike(variationalParameters, nParticles, nDimensions);
}

void VMCSolver::runMCWithMetropolis()
{   
    rOld = zeros<mat>(nParticles, nDimensions);
    rNew = zeros<mat>(nParticles, nDimensions);

    deltaE = 0;
    energySum = 0;
    energySquaredSum = 0;

    waveFunctionOld = 0;
    waveFunctionNew = 0;

    // initial trial positions
    for(int i = 0; i < nParticles; i++) {
        for(int j = 0; j < nDimensions; j++) {
            rOld(i,j) = stepLength * (ran2(&idum) - 0.5);
        }
    }
    rNew = rOld;

    for (int cycle = 0; cycle<nCycles; cycle ++) {
        // Save current value of waveFunction
        waveFunctionOld = waveFunction->f(rOld);

        // Test on new position
        for(int i = 0; i<nParticles; i++) {
            for (int j = 0; j<nDimensions; j++) {
                rNew = rOld +stepLength*(ran2(&idum)-0.5);
            }

            // For each particle move, check for acceptance:
            // recalculate value of waveFunction
            waveFunctionNew = waveFunction->f(rNew);

            if (ran2(&idum) <= (waveFunctionNew*waveFunctionNew)/(waveFunctionOld*waveFunctionOld)) {
                for (int j = 0; j<nDimensions; j++) {
                    rOld(i, j) = rNew(i, j);
                    waveFunctionOld = waveFunctionNew;
                }
            }
            else {
                for (int j = 0; j<nDimensions; j++) {
                    rNew(i, j) = rOld(i, j);
                }
            }

            // update energy
            deltaE = localEnergy(rNew);
            //cout << deltaE << endl;
            energySum += deltaE;
            energySquaredSum += deltaE*deltaE;

        }
        double energy = energySum/((cycle+1)*nParticles);
        cout << "Energy " << energy << endl;

    }
    double energy = energySum/(nCycles*nParticles);
    double energySquared = energySquaredSum/(nCycles*nParticles);
    cout << "Energy: " << energy << endl;
}


/**
 * @brief VMCSolver::localEnergy
 * @param r matrix of electron positions
 * @return local energy of the system, as defined in report
 */
double VMCSolver::localEnergy(const mat &r)
{
    double kinetic_energy = -0.5*waveFunction->laplacian(r, h)/waveFunction->f(r);
    //cout << "Kinetic energy: " << kinetic_energy << endl;

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
        for (int j = i+1; j<nParticles; j++) {
            r12 = 0;
            for (int k = 0; k<nDimensions; k++) {
                r12 += (r(i,k) - r(j,k))*(r(i,k)-r(j,k));
            }
            potential_energy += 1.0/sqrt(r12);
        }
    }

    // Summing and returning local energy
    //cout << potential_energy << " " << kinetic_energy << endl;
    return potential_energy+kinetic_energy;

}


