#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cmath>

#define setW 3

using namespace std;

//-------------------------------------------------------

// Singleton
class Manage final
{
    public:
        static const Manage& Instance()
        {
                static Manage theSingleInstance;
                return theSingleInstance;
        }

        int nfa(const vector<int>& gruz, const int& capacity, const int& comp) const;
        int ffa(const vector<int>& gruz, const int& capacity, const int& comp) const;
        int wfa(const vector<int>& gruz, const int& capacity, const int& comp) const;
        int bfa(const vector<int>& gruz, const int& capacity, const int& comp) const;

        mutable int (*ptr)(vector<int>& gruz);

    private:
        Manage(){};
        Manage(const Manage& root);
        Manage& operator=(const Manage&);
        Manage(Manage&& a);
        Manage& operator=(Manage&& a);

        int matrixWrite(const vector<int>& gruz, const vector<int>& vect,
                        const vector<int>& v) const;
};

int Manage::matrixWrite(const vector<int>& gruz, const vector<int>& vect,
                        const vector<int>& v) const
{
    cout << endl << "Table of results: " << endl << endl;
    cout << "  ";
    for(int i = 0; i < gruz.size(); ++i)
        cout << setw(setW) << gruz[i];

    cout << endl << endl;
    for(int i = 0; i < v.size(); ++i)
    {
        const int notNumber = -1; // no gruz with weight 0
        vector<int> vRes;
        for(int j = 0; j < vect.size(); ++j)
            if(vect[j] == i)
                vRes.push_back(j);
            else
                vRes.push_back(notNumber);

        cout << endl << "  ";
        for(int j = 0; j < gruz.size(); ++j)
            if(vRes[j] != notNumber)
                cout << setw(setW) << gruz[vRes[j]];
            else
                cout << setw(setW) << " ";

        cout << setw(setW) << "#" << i << " (" << v[i] << ")";
    }

    return 0;
}

int Manage::nfa(const vector<int>& gruz, const int& capacity, const int& comp) const
{
    cout << endl << endl << "NFA";

    vector<int> vect; // index - # of gruz, element = # of container
    vector<int> v; // Array where element = accumulate elements from gruz
    size_t nfaComp{comp};

    cout << endl << "gruz =  ";
    for (auto &i : gruz)
        cout << " " << i << " ";

    v.push_back(0);
    int k = 0;
    for(int i = 0; i < gruz.size(); ++i)
    {
        if((capacity - v[k]) >= gruz[i])
        {
            v[k] += gruz[i];
            vect.push_back(k);
        }
        else
        {
            v.push_back(gruz[i]);
            ++k;
            vect.push_back(k);
        }
        ++nfaComp;
    }

    cout << endl << "Containers =  ";
    for (auto &i : v)
        cout << " " << i << " ";
    cout << endl << "Compares =  " << nfaComp; // First container is clear but we add it
    cout << endl << "Count of containers =  " << v.size();
    for(int i = 0; i < vect.size(); ++i)
        cout << endl << "Container #" << vect[i] << "  ->  gruz index #" << i
            << "(" << gruz[i] <<")";

    matrixWrite(gruz, vect, v);
    return 0;
}

int Manage::ffa(const vector<int>& gruz, const int& capacity, const int& comp) const
{
    cout << endl << endl << "FFA";

    vector<int> vect;
    vector<int> v;
    size_t ffaComp{comp};

    cout << endl << "gruz =  ";
    for (auto &i : gruz)
        cout << " " << i << " ";

    v.push_back(0);
    int k = 0;
    for(int i = 0; i < gruz.size(); ++i)
    {
        if((capacity - v[k]) >= gruz[i])
        {
            v[k] += gruz[i];
            vect.push_back(k);
        }
        else
        {
            int j = 0;
            for(j = 0; j < k; ++j)
            {
                ++ffaComp;
                if((capacity - v[j]) >= gruz[i])
                {
                    v[j] += gruz[i];
                    vect.push_back(j);
                    break;
                }
            }
            if(j == k)
            {
                ++ffaComp;
                v.push_back(gruz[i]);
                ++k;
                vect.push_back(k);
            }
        }
        ++ffaComp;
    }

    cout << endl << "Containers =  ";
    for (auto &i : v)
        cout << " " << i << " ";
    cout << endl << "Compares =  " << ffaComp;
    cout << endl << "Count of containers =  " << v.size();
    for(int i = 0; i < vect.size(); ++i)
        cout << endl << "Container #" << vect[i] << "  ->  gruz index #"
            << i << "(" << gruz[i] <<")";

    matrixWrite(gruz, vect, v);
    return 0;
}

int Manage::wfa(const vector<int>& gruz, const int& capacity, const int& comp) const
{
    cout << endl << endl << "WFA";

    vector<int> vect;
    vector<int> v;
    size_t wfaComp{comp};

    cout << endl << "gruz =  ";
    for (auto &i : gruz)
        cout << " " << i << " ";

    v.push_back(0);
    int k = 0;
    for(int i = 0; i < gruz.size(); ++i)
    {
        if((capacity - v[k]) >= gruz[i])
        {
            v[k] += gruz[i];
            vect.push_back(k);
        }
        else
        {
            int vmin = 0;
            for(int j = 0; j < k; ++j)
            {
                ++wfaComp;
                if(v[j] < v[vmin])
                    vmin = j;
            }
            if((capacity - v[vmin]) >= gruz[i])
            {
                v[vmin] += gruz[i];
                vect.push_back(vmin);
            }
            else
            {
                v.push_back(gruz[i]);
                ++k;
                vect.push_back(k);
            }
            ++wfaComp;
        }
        ++wfaComp;
    }

    cout << endl << "Containers =  ";
    for (auto &i : v)
        cout << " " << i << " ";
    cout << endl << "Compares =  " << wfaComp;
    cout << endl << "Count of containers =  " << v.size();
    for(int i = 0; i < vect.size(); ++i)
        cout << endl << "Container #" << vect[i] << "  ->  gruz index #" << i
            << "(" << gruz[i] <<")";

    matrixWrite(gruz, vect, v);
    return 0;
}

int Manage::bfa(const vector<int>& gruz, const int& capacity, const int& comp) const
{
    cout << endl << endl << "BFA";

    vector<int> vect;
    vector<int> v;
    size_t bfaComp{comp};

    cout << endl << "gruz =  ";
    for (auto &i : gruz)
        cout << " " << i << " ";

    v.push_back(0);
    int k = 0;
    for(int i = 0; i < gruz.size(); ++i)
    {
        if((capacity - v[k]) >= gruz[i])
        {
            v[k] += gruz[i];
            vect.push_back(k);
        }
        else
        {
            int vmax = 0;
            for(int j = 0; j < k; ++j)
            {
                bfaComp += 4;
                if(((v[j] > v[vmax]) && ((capacity - v[j]) >= gruz[i]))
                   || (((capacity - v[vmax]) < gruz[i]) && (((capacity - v[j]) >= gruz[i]))))
                    vmax = j;
            }
            ++bfaComp;
            if((capacity - v[vmax]) >= gruz[i])
            {
                v[vmax] += gruz[i];
                vect.push_back(vmax);
            }
            else
            {
                v.push_back(gruz[i]);
                ++k;
                vect.push_back(k);
            }
        }
        ++bfaComp;
    }

    cout << endl << "Containers =  ";
    for (auto &i : v)
        cout << " " << i << " ";
    cout << endl << "Compares =  " << bfaComp;
    cout << endl << "Count of containers =  " << v.size();
    for(int i = 0; i < vect.size(); ++i)
        cout << endl << "Container #" << vect[i] << "  ->  gruz index #"
            << i << "(" << gruz[i] <<")";

    matrixWrite(gruz, vect, v);
    return 0;
}

//-------------------------------------------------

auto revBubleSort(vector<int>& gruz) -> int
{
    int comp = 0;
    for (vector<int>::iterator i = gruz.end() - 1; i > gruz.begin(); --i)
        for (vector<int>::iterator j = gruz.begin(); j < i; ++j)
        {
            if(*j < *(j + 1))
                swap(*j, *(j + 1));
            ++comp;
        }
    cout << endl << endl << "Sort compares =  " << comp;
    cout << endl << "After sort = ";
    copy(gruz.begin(), gruz.end(), ostream_iterator<int>(cout, " "));

    return comp;
}

//-------------------------------------------------

int main()
{
    cout << endl << "Start..." << endl << endl;

    const Manage& manager = Manage::Instance();

    // vectors
    //vector<int> gruz {2,4,3,1}; // 6 compares rev_buble_sort
    //vector<int> gruz{23,3,51,20,51,42,52,12,4,7,59,58,25,94,17};
    vector<int> gruz;
    vector<int> gruz1{5,25,84,27,36,5,46,29,13,57,24,95,82,45,14,67,34,64,43,50};
    vector<int> gruz2{87,8,76,78,88,84,3,51,54,99,32,60,76,68,39,12,26,86,94,39};
    vector<int> gruz3{95,70,34,78,67,1,97,2,17,92,52,56,1,80,86,41,65,89,44,19};
    vector<int> gruz4{5,25,84,27,36,5,46,29,13,57,24,95,82,45,14,67,34,64,43,50,87,8,76,78,88,84,3,51,54,99,32,60,76,68,39,12,26,86,94,39,95,70,34,78,67,1,97,2,17,92,52,56,1,80,86,41,65,89,44,19};

    const int capacity{100};

    // Work
    int meth;
    int vectormeth;
    cout << endl << "Enter the vector = ";
    cin >> vectormeth;
    switch(vectormeth)
    {
        case 1: gruz = move(gruz1);
                break;
        case 2: gruz = move(gruz2);
                break;
        case 3: gruz = move(gruz3);
                break;
        case 4: gruz = move(gruz4);
                break;
        default:
            break;
    }
    cout << "gruz =  ";
    for (auto &i : gruz)
    {
        cout << setw(setW) << i;
    }
    cout << endl << "Count of gruz =  " << gruz.size();
    cout << endl << "Weight of gruz =  " << accumulate(gruz.begin(), gruz.end(), 0);
    cout << endl << "Capacity of container =  " << capacity << endl;
    double min = ceil(static_cast<double>(accumulate(gruz.begin(), gruz.end(), 0)) / capacity);
    cout << "Min of containers =  " << min << endl;
    double max = static_cast<double>(11)/9 * min + 1;
    cout << "Max of containers (FFA, BFA) =  " << max << endl;

    // Without sort
    cout << endl << endl << "Example without sort:";

    cout << endl << "Enter the method = ";
    cin >> meth;
    switch(meth)
    {
        case 1: manager.nfa(gruz, capacity, 0);
                break;
        case 2: manager.ffa(gruz, capacity, 0);
                break;
        case 3: manager.wfa(gruz, capacity, 0);
                break;
        case 4: manager.bfa(gruz, capacity, 0);
                break;
        default:
            break;
    }

    // With sort
    cout << endl << endl;
    manager.ptr = revBubleSort;
    int comp = manager.ptr(gruz);
    cout << endl << "Example with sort:";
    switch(meth)
    {
        case 1: manager.nfa(gruz, capacity, comp);
                break;
        case 2: manager.ffa(gruz, capacity, comp);
                break;
        case 3: manager.wfa(gruz, capacity, comp);
                break;
        case 4: manager.bfa(gruz, capacity, comp);
                break;
        default:
            break;
    }

    // End
    cout << endl << endl;
    return 0;
}
