#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ostream>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

class account
{
protected:
public:
    string name;   // name of customer
    int accno;     // account number
    int pin;       // pincode for privacy
    char type;     // type of account {current & savings}
    double amount; // amount of money stored
    // time_t lastacc; // account last accessed for savings
    string branch; // bank branch

    account()
    {
        // default constructor
        name = "c_name";
        accno = 1000;
        pin = 0;
        type = 'x';
        amount = 0.00;
        branch = "none";
    }

    account(string name_, int accno_, int pin_, char type_, double amount_, string branch_)
    {
        this->name = name_;
        this->accno = accno_;
        this->pin = pin_;
        this->type = type_;
        this->amount = amount_;
        this->branch = branch_;
    }
    // function to create new account
    void create_account()
    {
        cout << "Enter Name : \n";
        getline(cin, name);
        cout << "Enter a 4 digit pin: ";
        while (true)
        {
            cin >> pin;
            if (pin < 10000 && pin > 999)
            {
                break;
            }
            else
            {
                cout << "Invalid Pin" << endl;
            }
        }
        cout << "Enter Account Type (c/s): \nc: Current Account\ns: Savings Account\n";

        while (true)
        {
            cin >> type;
            if (type == 's' || type == 'c')
            {
                break;
            }
            else
            {
                cout << "Enter correct account type (c/s)" << endl;
            }
        }
        cout << "Deposit base amount: " << endl;
        if (type == 's')
        {
            cout << "For savings account deposite minimum of Rs5000.00: " << endl;
            while (true)
            {
                cin >> amount;
                if (amount > 4999.99)
                {
                    break;
                }
                else
                {
                    cout << "Enter minimum of Rs5000.00" << endl;
                }
            }
        }
        else
        {
            cin >> amount;
        }
        cout << "Choose Branch:\n";
        cout << "1. Mohali\n2. Chandigarh\n3. Panchkula\n";
        cout << "your input: ";
        while (true)
        {
            int option;
            cin >> option;
            if (option == 1)
            {
                branch = "Mohali";
                break;
            }
            else if (option == 2)
            {
                branch = "Chandigarh";
                break;
            }
            else if (option == 3)
            {
                branch = "Panchkula";
                break;
            }
            else
            {
                cout << "Enter a valid branch\n";
            }
        }
    };
    // returns the type of account
    char check_type()
    {
        return type;
    };
    void set_accno(int n)
    {
        accno = n;
    }
    void display()
    {
        cout << name << endl;
        cout << accno << endl;
        cout << pin << endl;
        cout << type << endl;
        cout << amount << endl;
        cout << branch << endl;
        cout << endl;
    }
};
class customer : public account
{
    vector<account> accounts; // an array of accounts to be stored
    string file_name;
    string account_no;

public:
    customer(string file)
    {
        file_name = file;
    }
    //add a new account
    void add_account()
    {
        account obj;
        obj.create_account();
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accno == obj.accno)
            {
                obj.accno++;
            }
        }
        accounts.push_back(obj);
    }
    //display all accounts
    void display_all()
    {
        if (accounts.size() == 0)
        {
            cout << "No account exist \n";
            return;
        }
        for (int i = 0; i < accounts.size(); i++)
        {
            accounts[i].display();
            cout << endl;
        }
    }
    // modify account info
    void modify( int accno_)
    {
        string namex;
        int pin;
        cout << "Account Update Portal:\n";
        cout<<"Enter your account number: ";
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accno_== accounts[i].accno)
            {
                cout << "Default Name: " << accounts[i].name << endl;
                cout << "Update Name:\n";
                cin>>namex;
                cout << "Reset Pin;\n";
                while (true)
                {
                    cin >> pin;
                    if (pin < 10000 && pin > 999)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Pin" << endl;
                    }
                }
                accounts[i].pin=pin;
                if(!namex.empty()){
                    accounts[i].name=namex;
                }
                return;
            }
        }
    };
    //Delete account
    void delete_account(int accno_){
        
        cout << "Account Delete Portal:\n";
        for(vector<account>::iterator i=accounts.begin();i!=accounts.end();i++){
            if(i->accno==accno_){
                accounts.erase(i);
                return;
            }
        }
    }; // delete account
    //Display Account Specific User
    void c_show_account(int accno_){
        cin>>accno_;
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accno_== accounts[i].accno)
            {
                accounts[i].display();
            }
        }
    }; // show customer's account
    void parchi();

    void store()
    {
        ofstream t(file_name, ios::trunc);
        t.close();
        ofstream f(file_name, ios::app);
        if (!f.is_open())
        {
            return;
        }

        for (int i = 0; i < accounts.size(); i++)
        {
            f.write((char *)&accounts[i].accno, sizeof(accounts[i].accno));
            f.write((char *)accounts[i].name.c_str(), accounts[i].name.length() + 1);
            f.write((char *)&accounts[i].pin, sizeof(accounts[i].pin));
            f.write((char *)&accounts[i].type, sizeof(accounts[i].type));
            f.write((char *)&accounts[i].amount, sizeof(accounts[i].amount));
            f.write((char *)accounts[i].branch.c_str(), accounts[i].branch.length() + 1);
        }
        f.close();
    }

    void load()
    {
        ifstream f(file_name);
        if (!f.is_open())
        {
            return;
        }
        f.seekg(0, f.end);
        int n = f.tellg();
        f.seekg(0, f.beg);
        while (f.tellg() != n)
        {
            account b;
            f.read((char *)&b.accno, sizeof(b.accno));
            getline(f, b.name, '\0');
            f.read((char *)&b.pin, sizeof(b.pin));
            f.read((char *)&b.type, sizeof(b.type));
            f.read((char *)&b.amount, sizeof(b.amount));
            getline(f, b.branch, '\0');
            accounts.push_back(b);
        }
        f.close();
    }
};

// class savings : public virtual account{
//     public:
//     void t_limit();//since saving accounts have transaction limit this function checks if withdraw amount doesn't exeecds
//     void s_minimum();//check for minimum required money stored
// };
// class current : public virtual account{
//     public:
//     void c_minimum();//check for minimum required money stored
// };
// class transaction : public savings,public current{
//     public:
//     void deposit();//to deposit money
//     void withdraw();//to withdraw money
// };

// class employee : public account{
//     int accessed_last; //account number last accessed
//     time_t accessed_time;//time of the last accessed
//     public:
//     void show_account() const; //function to display all account
//     void display_customer() const;//checks for specific account
//     void last_entry() const;//checks for the last accessed
// };
// class branch : public account{
//     public:
//     void check_branch();

// };

int main()
{
    customer cust("data.txt");
    cust.load();
    bool flag = false;
    while (true)
    {
        int option;
        cin >> option;
        cin.ignore();
        int id;
        cin>>id;
        switch (option)
        {
        case 1:
            cust.add_account();
            cust.store();
            cout << "Account Added Successfully\n";
            break;
        case 2:
            cust.display_all();
            cout << "All Displayed!\n";
            break;
        case 3:
            cust.modify(id);
            cust.store();
            cout<<"Updated! Successfully\n";
            break;
        case 4:
            cust.delete_account(id);
            cust.store();
            cout<<"Account deleted successfully!\n";
            break;
        case 5:
            cust.c_show_account(id);
            break;
        default:
            break;
        }
    }
    return 0;
}