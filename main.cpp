#include <iostream>
#include "vmcapplication.h"

using namespace std;

int main()
{
    string cfgFile = "/home/henrik/Dropbox/Henrik/Emner/FYS4411/FYS4411-project1/config/v01.cfg";
    VMCApplication app(cfgFile);
    app.run();
    return 0;
}

