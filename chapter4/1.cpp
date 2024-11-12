#include<iostream>
using namespace std;
int main()
{
    int n=1000,x=6;
    const int Mod=2023;
    for(int i=1;i<=336;i++)
    {
        x=(x*10+6)%Mod;
    }
    cout<<x<<endl;
    return 0;
}