#include "vmcapplication.h"
#include <string>


VMCApplication::VMCApplication(string cfgFile)
{
    // Try read settings from file
    try {
        cfg.readFile(cfgFile.c_str());
    } catch (const FileIOException &fioex) {
        cerr << "I/O error while reading config file." << endl;
        exit(EXIT_FAILURE);
    }
    solver = new VMCSolver(cfg);
}

void VMCApplication::run()
{
    solver->runMCWithMetropolis();
}
