#include <bits/stdc++.h>
using namespace std;

void left_fact(string prod)
{
    string frst, scnd, modifi_prod = "", new_prod = "", temp;

    int i = 0, pos;
    char x1 = prod[0];
    string y = "", x = "";
    x += x1;
    y += x1;
    y += "'";

    pos = prod.find("/");
    frst = prod.substr(6, pos - 6);
    scnd = prod.substr(pos + 1);
    int l1 = frst.length(), l2 = scnd.length();
    size_t pos1= scnd.find("/");

    if(pos1 != string::npos)
    {
        temp = scnd.substr(pos1);
        scnd.erase(pos1);
    }

    else
        temp = "";

    while(true)
    {
        if(frst[i] != scnd[i])
            break;

        modifi_prod += frst[i];
        i++;
    }

    if(i == 0 or modifi_prod == "")
        cout<<"There is No Left Factoring";

    else
    {
        string a = frst.substr(i ,l1), b = scnd.substr(i, l2);

        if(a == "")
            a = "epsilon";

        else if(b == "")
            b = "epsilon";

        new_prod += a + "/" + b;
        modifi_prod +=( y + temp );
        cout<<"The New Production Rule after Removing Left Factoring is :- \n";
        cout<<"\n"<<x<<" --> "<<modifi_prod<<"\n";
        cout<<y<<" --> "<<new_prod;
        cout<<"\n";
    }
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
        left_fact(v[i]);
    }
    cout<<"\n";

    return 0;
}
