#ifndef VMCSOLVER_H
#define VMCSOLVER_H

#include <armadillo>

using namespace arma;
using namespace std;

class VMCSolver
{
public:
    VMCSolver();

protected:
    double waveFunction(const mat &r);
};

#endif // VMCSOLVER_H
