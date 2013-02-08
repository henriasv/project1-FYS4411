#ifndef VMCAPPLICATION_H
#define VMCAPPLICATION_H

#include "vmcsolver.h"
#include <libconfig.h++>

class VMCApplication
{
public:
    VMCApplication(string cfgFile);
    void run();

protected:
    VMCSolver* solver;
    Config cfg;
};

#endif // VMCAPPLICATION_H
