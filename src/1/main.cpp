#include "head.h"

using namespace std;

int main()
{
    const Manage& manager = Manage::Instance();

    // Vectors
    vector<int> q01 {0,2,8,2,3,0,4,2,1,5,2,9,8,4,1,6,3,6,4,5};
    vector<int> q02 {5,5,4,7,6,5,6,9,3,7,4,5,2,5,4,7,4,4,3,0};
    vector<int> q11 {8,0,7,7,8,8,0,5,5,9,3,6,7,6,3,1,2,8,9,3};
    vector<int> q12 {7,8,6,8,8,4,3,1,4,9,2,0,6,8,9,2,6,6,4,9};
    vector<int> q21 {9,7,3,7,6,0,9,0,1,9,5,5,0,8,8,4,6,8,4,1};
    vector<int> q22 {5,0,4,8,7,1,7,2,7,2,2,6,1,0,6,1,5,9,4,9};
    vector<int> q31 {0,2,8,2,3,0,4,2,1,5,2,9,8,4,1,6,3,6,4,5,8,0,7,7,8,8,0,5,5,9,3,6,7,6,3,1,2,8,9,3,9,7,3,7,6,0,9,0,1,9,5,5,0,8,8,4,6,8,4,1};
    vector<int> q32 {5,5,4,7,6,5,6,9,3,7,4,5,2,5,4,7,4,4,3,0,7,8,6,8,8,4,3,1,4,9,2,0,6,8,9,2,6,6,4,9,5,0,4,8,7,1,7,2,7,2,2,6,1,0,6,1,5,9,4,9};

    // Algorithms
    Arr2D<int> a0;
    Meth* pareto0 = new Meth2DPareto();
    Meth* sleyter0 = new Meth2DSleyter();

    // Work
    cout << endl << endl << "----------------";
    cout << endl << "First example:";
    a0.init(q01, q02);
    manager(a0, pareto0);
    manager(a0, sleyter0);

    cout << endl << endl << "----------------";
    cout << endl << "Second example:";
    a0.init(q11, q12);
    manager(a0, pareto0);
    manager(a0, sleyter0);

    cout << endl << endl << "----------------";
    cout << endl << "Third example:";
    a0.init(q21, q22);
    manager(a0, pareto0);
    manager(a0, sleyter0);

    cout << endl << endl << "----------------";
    cout << endl << "Fourth example:";
    a0.init(q31, q32);
    manager(a0, pareto0);
    manager(a0, sleyter0);

    delete pareto0;
    delete sleyter0;
    cout << endl << endl;
    return 0;
}
