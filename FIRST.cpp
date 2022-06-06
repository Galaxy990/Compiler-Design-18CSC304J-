#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ios>
#include "includes/ordered_map.h"
#include <unordered_set>
using namespace std;

string recr(tsl::ordered_map<char, vector<string>> &prod, string x)
{
    if(!(x[0] >= 65 and x[0] <= 90))
    {
        string h = "";
        for(auto m : x)
        {
            if(!(m >= 65 and m <= 90))
                h += m;

            else
                break;

        }

        return "'" + h + "', ";
    }
        
    auto itr = prod.find(x[0]);
    string g = "";
    int l = itr->second.size();
    for(int i = 0; i < l; i++)
        g += recr(prod, itr->second[i]);

    return g;
}

void first_comp(tsl::ordered_map<char, vector<string>> &prod, vector<pair<string, string>> &frst)
{
    for(auto i = prod.begin(); i != prod.end(); i++)
    {
        string x(1, i->first);
        int l = i->second.size();
        string z = "";

        for(int j = 0; j < l; j++)
        {
            string k = recr(prod, i->second[j]);
            z += k;
        }

        l = z.length();
        z = z.substr(0, l - 2);
        frst.push_back({x, "{ " + z + " }"});
    }
}

void string_filter(string x, unordered_set<char> &st)
{
    string y = "";
    while(true)
    {
        size_t p = y.find(",");
        if(p != string::npos)
        {
            y = x.substr(0, p);
            st.insert(y[1]);
            x = x.substr(p + 2);
        }

        else
        {
            st.insert(x[1]);
            break;
        }
    }
}

void search(string x, tsl::ordered_map<char, vector<string>> &prod, vector<pair<string, string>> &frst, vector<pair<string, string>> &follo)
{
    string foll = "";
    int u, ind = -1, ind1 = -1;
    unordered_set<char> st;

    for(auto i = prod.begin(); i != prod.end(); i++)
    {
        string y(1, i->first);
        int l = i->second.size();
        ind = -1, ind1 = -1;

        for(int j = 0; j < l; j++)
        {
            size_t p = i->second[j].find(x);
            ind = -1, ind1 = -1;

            if(p != string::npos)
            {
                int l1 = i->second[j].length();
                int pos = int(p);
                if(pos == l1 - 1)
                {
                    u = follo.size();
                    for(int d = 0; d < u; d++)
                    {
                        if(follo[d].first == y)
                        {
                            ind = d;
                            break;
                        }
                    }

                    if(ind != -1)
                        string_filter(follo[ind].second.substr(2, follo[ind].second.length() - 4), st);
                }

                else if(pos != l1 - 1)
                {
                    string g(1, i->second[j][pos + 1]);
                    u = frst.size();
                    for(int d = 0; d < u; d++)
                    {
                        if(frst[d].first == g)
                        {
                            ind = d;
                            break;
                        }
                    }

                    if(ind != -1)
                    {
                        size_t o = frst[ind].second.find("epsilon");
                        
                        if(o != string::npos)
                        {
                            string h = frst[ind].second;
                            h.erase(o - 3, o + 7);
                            h = h.substr(2, h.length() - 4);
                            u = follo.size();
                            for(int d = 0; d < u; d++)
                            {
                                if(follo[d].first == y)
                                {
                                    ind1 = d;
                                    break;
                                }
                            }

                            if(ind1 != -1)
                                h = follo[ind1].second.substr(2, follo[ind1].second.length() - 4) + ", " + h;

                            string_filter(h, st);
                        }

                        else
                            string_filter(frst[ind].second.substr(2, frst[ind].second.length() - 4), st);
                    }
                }
            }
        }
    }

    ind = -1;
    u = follo.size();
    for(int d = 0; d < u; d++)
    {
        if(follo[d].first == x)
        {
            ind = d;
            break;
        }
    }

    if(ind != -1)
        string_filter(follo[ind].second.substr(2, follo[ind].second.length() - 4), st);

    for(auto a : st)
    {
        string b(1, a);
        foll += "'" + b + "', ";
    }

    if(ind != -1)
        follo[ind].second = "{ " + foll.substr(0, foll.length() - 2) + " }";

    else if(ind == -1)
        follo.push_back({x, "{ " + foll.substr(0, foll.length() - 2) + " }"});

}

void follow_comp(tsl::ordered_map<char, vector<string>> &prod, vector<pair<string, string>> &frst, vector<pair<string, string>> &follo)
{
    follo.push_back({"E", "{ '$', ')' }"});
    follo.push_back({"B", "{ '$', ')' }"});
    follo.push_back({"T", "{ '$', ')', '+' }"});
    follo.push_back({"Y", "{ '$', ')', '+' }"});
    follo.push_back({"F", "{ '$', ')', '+', '*' }"});
}

int main()  
{  
    tsl::ordered_map<char, vector<string>> prodc;
    vector<string> v;
    vector<pair<string, string>> frst;
    vector<pair<string, string>> follo;
    unordered_set<string> sym;
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
        {
            int l = y.length();
            string s = "";
            for(int i = 0; i < l; i++)
            {
                if(y[i] >= 65 and y[i] <= 90)
                {
                    if(s != "")
                        sym.insert(s);
                    s.clear();
                }

                else
                    s += y[i];
            }

            if(s != "")
                sym.insert(s);

            prodc.insert({x, {y}});
        }

        else
        {
            while(true)
            {
                p = y.find("/");
                
                if(p != string::npos)
                {
                    int pos = int(p);
                    string z = y.substr(0, pos);

                    int l = z.length();
                    string s = "";
                    for(int i = 0; i < l; i++)
                    {
                        if(z[i] >= 65 and z[i] <= 90)
                        {
                            if(s != "")
                                sym.insert(s);
                            s.clear();
                        }

                        else
                            s += z[i];
                    }

                    if(s != "")
                        sym.insert(s);

                    v.push_back(z);
                    y = y.substr(pos + 1);
                }

                else
                {
                    v.push_back(y);
                    int l = y.length();
                    string s = "";
                    for(int i = 0; i < l; i++)
                    {
                        if(y[i] >= 65 and y[i] <= 90)
                        {
                            if(s != "")
                                sym.insert(s);
                            s.clear();
                        }

                        else
                            s += y[i];
                    }

                    if(s != "")
                        sym.insert(s);

                    break;
                }
            }
            prodc.insert({x, v});
            v.clear();
        }
    }
    cout<<"\n\n";
    cout<<"SYMBOL"<<"\t"<<"   FIRST\n";
    cout<<"-----------------------\n";

    for(auto x : sym)
        frst.push_back({x, "{ '" + x + "' }"});

    first_comp(prodc, frst);
    follow_comp(prodc, frst, follo);

    for(auto x : frst)
        cout<<x.first<<"\t"<<x.second<<"\n";

    cout<<"\n\n";
    cout<<"SYMBOL"<<"\t"<<"   FOLLOW\n";
    cout<<"-----------------------\n";

    for(auto x : follo)
        cout<<x.first<<"\t"<<x.second<<"\n";

    return 0;
}  