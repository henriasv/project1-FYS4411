#include "vmcapplication.h"
#include <string>


VMCApplication::VMCApplication(string cfgFile)
{
    cfg = new Config();
    cfg->readFile(cfgFile.c_str());
    solver = new VMCSolver(*cfg);
}

void VMCApplication::run()
{
    solver->runMCWithMetropolis();
}
