#include<iostream>
#include<stdlib.h>
using namespace std;
 
int main(){
    // int pin;
    // while(true){
    //     cin>>pin;
    //     if(pin<10000&&pin>999){
    //         break;
    //     }
    //     else{
    //         cout<<"EH WRONG BIATCH!"<<endl;
    //     }
    // }
    // cout<<pin;
    char type;
    while(true){
            cin>>type;
            if(type=='s'||type=='c'){
                break;
            }
            else{
                cout<<"Enter correct account type (c/s)"<<endl;
            }
        }
    cout<<type;
    double amount;
    if(type=='s'){
            cout<<"For savings account deposite minimum of Rs5000.00: "<<endl;
            while(true){
                cin>>amount;
                if(amount>4999.99){
                    break;
                }
                else{
                    cout<<"Enter minimum of Rs5000.00"<<endl;
                }
            }
        }
        else{
            cin>>amount;
        }
    return 0;
}