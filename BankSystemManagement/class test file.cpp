#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ostream>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

int main(){
    int a[]={1,2,3,4,5,6};
    int n=1;
    int x;
    for(int i=0;i<8;i++){
        x=n;
        if(a[i]==x){
            n++;
        }
    }
    cout<<x;
    return 0;
        string name;    // name of customer
    int accno;      // account number
    int pin;        // pincode for privacy
    char type;      // type of account {current & savings}
    double amount;  // amount of money stored
    // time_t lastacc; // account last accessed for savings
    string branch;  // bank branch
}