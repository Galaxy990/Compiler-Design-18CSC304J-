#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ios>
using namespace std;

void left_recr(string prod)
{
    string z = prod;
    prod = prod.substr(6);
    int i = 0, l = prod.length(), l1, l2;
    vector<string> alpha, beta;
    string x = prod, y, bta = "", alph = "", a = "", b = "";
    a += z[0];
    b += z[0];
    b += "'";

    while(true)
    {
        size_t pos = x.find("/");
        if(pos != string::npos)
        {
            int p = int(pos);
            y = x.substr(i, p - i);
            x = x.substr(pos + 1);

            if(y[0] == z[0])
                alpha.push_back(y);

            else
                beta.push_back(y);
        }

        else
        {
            if(x[0] == z[0])
                alpha.push_back(x);

            else
                beta.push_back(x);

            break;
        }
    }

    for(auto j : beta)
        bta += j + b + "/";

    l1 = bta.length();
    bta = bta.substr(0, l1 - 1);

    for(auto j : alpha)
    {
        l2 = j.length();
        alph += j.substr(1, l2 - 1) + b + "/";
    }

    alph += "epsilon";

    cout<<"The New Production Rule after Removing Left Recursion is :- \n";
    cout<<a<<" --> "<<bta<<"\n";
    cout<<b<<" --> "<<alph<<"\n";
}

int main()  
{  
    vector<string> v;
    string prod1;
    int n,i;
    cout<<"Input No. of Production Rules :- ";
    cin>>n;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"\nInput the Set of Production Rules :- \n";
    
    for(i = 0; i < n; i++)
    {
        getline(cin, prod1);
        v.push_back(prod1);
    }
    
    int l = v.size();

    for(i = 0; i < l; i++)
    {
        cout<<"\n(Rule "<<i + 1<<"): ";
        left_recr(v[i]);
    }
    cout<<"\n";

    return 0;
}  
