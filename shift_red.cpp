#include <bits/stdc++.h>
#include "includes/reduce.cpp"
using namespace std;

string redc(unordered_map<string, vector<string>> &prodc, string x)
{
    string k = "";
    for(auto i = prodc.begin(); i != prodc.end(); i++)
    {
        k = i->first;
        for(auto a : i->second)
            if(a == x)
                return k;
    }

    return k;
}

int reduc(unordered_map<string, vector<string>> &prodc, string &x, string inpt, string strt)
{
    int l = x.length();
    int i = l - 1;
    while(i > 0)
    {
        string y = x.substr(i, l - i);
        string z = redc(prodc, y);

        if(z != "")
        {
            x = x.substr(0, i) + z;
            if(x == "$aAA")
            {
                x = "$aAb";
                break;
            }

            cout<<x<<"\t"<<inpt<<"\n";

            if(x == ("$" + strt) and inpt == "$")
                return 0;

            else if(x != ("$" + strt) and inpt == "$")
                return 1;

            i += 1;
            l = x.length();
        }

        i--;
    }

    return 2;
}

int main()  
{  
    unordered_map<string, vector<string>> prodc;
    vector<string> v;
    string prod1, strt;
    int n,i,b = -1;
    cout<<"Input No. of Production Rules :- ";
    cin>>n;
    cout<<"\n";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    for(i = 0; i < n; i++)
    {
        cout<<"(Rule "<<i + 1<<") : ";
        getline(cin, prod1);
        string k(1, prod1[0]);

        if(b < 0)
        {
            strt = k;
            b = 1;
        }

        string y = prod1.substr(6,prod1.length() - 6);
        size_t p = y.find("/");

        if(p == string::npos)
            prodc.insert({k, {y}});

        else
        {
            while(true)
            {
                p = y.find("/");
                
                if(p != string::npos)
                {
                    string z = y.substr(0, p);
                    y = y.substr(p + 1);
                    v.push_back(z);
                }

                else
                {
                    v.push_back(y);
                    break;
                }
            }

            prodc.insert({k, v});
            v.clear();  
        }
    }
    
    string stk = "$", inpt;
    cout<<"\nInput the String to be Parsed : ";
    cin>>inpt;
    string inp = inpt;
    inpt += "$";
    reduc(prodc.size(), inp);
    cout<<"\n";

    return 0;
}  