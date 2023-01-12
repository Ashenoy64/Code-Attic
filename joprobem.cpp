#include<bits/stdc++.h>

using namespace std;

void solve(int start,int inc,vector<string>  v)
{
    while(v.size()!=1)
    {
        int pos=start+inc-1;
        if(pos>=v.size())
        {
            pos=pos-v.size();
        }
        cout<<"Person who is removed:"<<*(v.begin()+pos) <<"\n";
        v.erase(v.begin()+pos);
        start=pos;
    }   
    cout<<"The person who escapes is:"<<v[0]; 
}

// vector<int> slice(vector<int>::iterator it,vector<int>::iterator end)
// {
//     vector<int> v;
//     for(;it!=end;it++)
//     {
//         v.push_back(*it);
//     }

//     return v;
// } 


int main()
{
    string s;
    int n;
    cout<<"Enter Number of people:"<<"\n";
    cin>>n;
    vector<string> v;
    cout<<"Enter the names"<<"\n";
    while(n--)
    {
        cin>>s;
        v.push_back(s);
    }
    cout<<"Enter the increment:";
    cin>>n;
    solve(1,n,v);
}