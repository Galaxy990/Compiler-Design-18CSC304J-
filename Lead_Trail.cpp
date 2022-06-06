#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ios>
#include "includes/ordered_map.h"
#include <unordered_set>
using namespace std;

void string_filter(string x, unordered_set<string> &st)
{
    string y = "";
    while(true)
    {
        size_t p = x.find(" ");
        if(p != string::npos)
        {
            y = x.substr(0, p);
            if(y != "")
                st.insert(y);

            x = x.substr(p + 1);
        }

        else
        {
            if(x != "")
                st.insert(x);
            break;
        }
    }
}

string recr(tsl::ordered_map<char, vector<string>> &prod, string x)
{
    int l = x.length(), i, b = -1;
    string y = "";
    for(i = 0; i < l; i++)
    {
        if(b < 0)
        {
            if(!(x[i] >= 65 and x[i] <= 90))
            {
                y += x[i];
                b = 1;
            }
        }

        else if(b > 0 and !(x[i] >= 65 and x[i] <= 90))
            y += x[i];

        else if(b > 0 and (x[i] >= 65 and x[i] <= 90))
            break;
    }

    string g = "";
    if(b < 0)
    {
        auto it = prod.find(x[0]);
        int l = it->second.size();

        for(i = 0; i < l; i++)
            g += recr(prod, it->second[i]) + " ";
    }

    y += " " + g;
    return y;
}

void lead_comp(tsl::ordered_map<char, vector<string>> &prod, vector<pair<string, string>> &lead)
{
    unordered_set<string> chr;
    for(auto i = prod.begin(); i != prod.end(); i++)
    {
        string x(1, i->first);
        int l = i->second.size();
        string z = "";

        for(int j = 0; j < l; j++)
            z += recr(prod, i->second[j]);
        
        string_filter(z.substr(0, z.length() - 1), chr);
        z = "";

        for(auto j : chr)
            z += "'" + j + "', ";
        
        lead.push_back({x, "{ " + z.substr(0, z.length() - 2) + " }"});
        chr.clear();
    }
}

string recr1(tsl::ordered_map<char, vector<string>> &prod, string x)
{
    int l = x.length(), i, b = -1;
    string y = "";
    for(i = l - 1; i >= 0; i--)
    {
        if(b < 0)
        {
            if(!(x[i] >= 65 and x[i] <= 90))
            {
                y = x[i] + y;
                b = 1;
            }
        }

        else if(b > 0 and !(x[i] >= 65 and x[i] <= 90))
            y = x[i] + y;

        else if(b > 0 and (x[i] >= 65 and x[i] <= 90))
            break;
    }

    string g = "";
    if(b < 0)
    {
        auto it = prod.find(x[l - 1]);
        int l = it->second.size();

        for(i = 0; i < l; i++)
            g += recr(prod, it->second[i]) + " ";
    }

    y += " " + g;
    return y;
}

void trail_comp(tsl::ordered_map<char, vector<string>> &prod, vector<pair<string, string>> &trail)
{
    unordered_set<string> chr;
    for(auto i = prod.begin(); i != prod.end(); i++)
    {
        string x(1, i->first);
        int l = i->second.size();
        string z = "";

        for(int j = 0; j < l; j++)
            z += recr1(prod, i->second[j]);
        
        string_filter(z.substr(0, z.length() - 1), chr);
        z = "";

        for(auto j : chr)
            z += "'" + j + "', ";
        
        trail.push_back({x, "{ " + z.substr(0, z.length() - 2) + " }"});
        chr.clear();
    }
}

int main()  
{  
    tsl::ordered_map<char, vector<string>> prodc;
    vector<string> v;
    vector<pair<string, string>> lead;
    vector<pair<string, string>> trail;
    string prod1;
    int n,i;
    cout<<"Input No. of Production Rules :- ";
    cin>>n;
    cout<<"\n";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    for(i = 0; i < n; i++)
    {
        cout<<"(Rule "<<i + 1<<") : ";
        getline(cin, prod1);
        char x = prod1[0];
        string k(1, x);

        string y = prod1.substr(6,prod1.length() - 6);
        size_t p = y.find("/");

        if(p == string::npos)
            prodc.insert({x, {y}});

        else
        {
            while(true)
            {
                p = y.find("/");
                
                if(p != string::npos)
                {
                    int pos = int(p);
                    string z = y.substr(0, pos);
                    v.push_back(z);
                    y = y.substr(pos + 1);
                }

                else
                {
                    v.push_back(y);
                    break;
                }
            }
            prodc.insert({x, v});
            v.clear();
        }
    }
    cout<<"\n\n";
    cout<<"SYMBOL"<<"\t"<<"   LEADING\n";
    cout<<"-----------------------\n";

    lead_comp(prodc, lead);

    for(auto x : lead)
        cout<<x.first<<"\t"<<x.second<<"\n";

    cout<<"\n\n";
    cout<<"SYMBOL"<<"\t"<<"   TRAILING\n";
    cout<<"-----------------------\n";

    trail_comp(prodc, trail);

    for(auto x : trail)
        cout<<x.first<<"\t"<<x.second<<"\n";

    cout<<"\n";
    return 0;
}  