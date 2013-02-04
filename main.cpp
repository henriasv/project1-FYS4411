#include <iostream>
#include <vmcsolver.h>

using namespace std;

int main()
{
    VMCSolver* solver = new VMCSolver();
    solver->run();
    cout << "Hello World!" << endl;
    return 0;
}

