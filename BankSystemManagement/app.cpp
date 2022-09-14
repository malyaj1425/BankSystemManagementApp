#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ostream>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;
// CURRENT ACCOUNT CLASS
class current
{
public:
    bool flag;
    current()
    {
        flag = false;
    }
    void c_minimum(double n)
    {
        if (n > 999.00)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }
    } // check for minimum required money stored
};

// SAVINGS ACCOUNT CLASS
class savings
{
public:
    bool flag;
    bool flag2;
    savings()
    {
        flag = false;
        flag2 = false;
    }
    void t_limit(double m)
    {
        if (m > 10000.00 || m < 1)
        {
            flag2 = false;
        }
        else
        {
            flag2 = true;
        }
    }; // since saving accounts have transaction limit this function checks if withdraw amount doesn't exeecds
    void s_minimum(double n)
    {
        if (n >= 5000.00)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }
    } // check for minimum required money stored
};

// TRANSACTIONS TO BE DONE
class transaction
{
    double amount;
    double wamount;

public:
    transaction(){

    };
    void deposit()
    {
        cout << "DEPOSIT AMOUNT: \n";
        cin >> amount;
    }; // to deposit money
    void withdraw()
    {
        cout << "ENTER AMOUNT: \n";
        cin >> wamount;
    }; // to withdraw money
    friend class customer;
};

// ACCOUNT CLASS
class account
{

protected:
    string name;    // name of customer
    int accno;      // account number
    int pin;        // pincode for privacy
    char type;      // type of account {current & savings}
    double amount;  // amount of money stored
    time_t lastacc; // account last accessed for savings
    string branch;  // bank branch

public:
    account()
    {
        // default constructor
        name = "c_name";
        accno = 1000;
        pin = 0;
        type = 'x';
        amount = 0.00;
        lastacc = time(0);
        branch = "none";
        
    }

    account(string name_, int accno_, int pin_, char type_, double amount_,time_t last_, string branch_)
    {
        this->name = name_;
        this->accno = accno_;
        this->pin = pin_;
        this->type = type_;
        this->amount = amount_;
        this->lastacc = last_;
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
                savings s_type;
                s_type.s_minimum(amount);
                if (s_type.flag)
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
            while (true)
            {
                current obj;
                cin >> amount;
                obj.c_minimum(amount);
                if (obj.flag)
                {
                    break;
                }
                else
                {
                    cout << "Deposit minimum of Rs1000.0\n";
                }
            }
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
        cout <<"NAME: "<< name << endl;
        cout <<"ACCOUNT NO: "<< accno << endl;
        cout <<"PIN: "<< pin << endl;
        cout <<"ACCOUNT TYPE: "<< type << endl;
        cout <<"MONEY STORED: "<< amount << endl;
        cout <<"BRANCH: "<< branch << endl;
        cout << endl;
    }

    friend class customer;
    friend class employee;
};

class employee : public account
{
    int accessed_last;    // account number last accessed 
    time_t accessed_time; // time of the last accessed
    vector<account> accounts;
    string file_name;

public:
int search_account; // account number to search
    employee();
    employee(string file)
    {
        file_name = file;
    }
    void add_account()
    {
        account obj;
        obj.create_account();
        accounts.push_back(obj);
    }

    // void show_account() const;     // function to display all account
    void display_customer(){
        cout<<"Enter account no. of holder you wish to search: ";
        cin>>search_account;
        return;
    }; // checks for specific account
    void last_entry(int id)
    {
        accounts[0].accno = id;
        return;
    }; // checks for the last accessed
    void return_entry()
    {
        cout << "LAST PERSON TO ACCESS BANK WAS ID: ";
        cout << accounts[0].accno;
        return;
    }
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
            accounts.push_back(b);
        }
        f.close();
    }
};
class branch
{
public:
    branch();
    void show_branchs()
    {
        cout << "BRANCHES AVAILABLE FOR BANK OF DREAMING:\n1. Mohali\n2. Chandigarh\n3. Panchkula\n";
    };
};

// CUSTOMER CLASS;
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
    // add a new account
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
    bool search_account(int n)
    {
        bool x = false;
        for (int i = 0; i < accounts.size(); i++)
        {
            if (n == accounts[i].accno)
            {
                x = true;
            }
        }
        return x;
    }
    bool login(int account_number, int pin)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (account_number == accounts[i].accno)
            {
                if (pin == accounts[i].pin)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    // display all accounts
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
    void modify(int accno_)
    {
        string namex;
        int pin;
        cout << "Account Update Portal:\n";
        cout << "Enter your account number: ";
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accno_ == accounts[i].accno)
            {
                cout << "Default Name: " << accounts[i].name << endl;
                cout << "Update Name:\n";
                cin >> namex;
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
                accounts[i].pin = pin;
                if (!namex.empty())
                {
                    accounts[i].name = namex;
                }
                return;
            }
        }
    };
    // Delete account
    void delete_account(int accno_)
    {

        cout << "Account Delete Portal:\n";
        for (vector<account>::iterator i = accounts.begin(); i != accounts.end(); i++)
        {
            if (i->accno == accno_)
            {
                accounts.erase(i);
                break;
            }
        }
    }; // delete account

    // Display Account Specific User
    void c_show_account(int accno_)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accno_ == accounts[i].accno)
            {
                accounts[i].display();
                break;
            }
        }
    }; // show customer's account
    void deposit(int id, int pn)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (id == accounts[i].accno && pn == accounts[i].pin)
            {
                transaction obj;
                obj.deposit();
                accounts[i].amount += obj.amount;
                accounts[i].lastacc=time(0);
                break;
            }
        }
    }
    void withdraw(int id, int pn)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (id == accounts[i].accno && pn == accounts[i].pin)
            {
                transaction obj;
                obj.withdraw();
                if (obj.wamount > accounts[i].amount)
                {
                    cout << "TRANSACTION FAILED INSUFFICIENT BALANCE!\n";
                    break;
                }
                else if (accounts[i].check_type() == 's')
                {
                    savings sobj;
                    sobj.t_limit(obj.wamount);
                    if (sobj.flag2)
                    {
                        accounts[i].amount -= obj.wamount;
                        accounts[i].lastacc=time(0);
                        break;
                    }
                    else
                    {
                        cout << "WITHDRAW AMOUNT EXCEEDED!\n";
                        break;
                    }
                }
                else
                {
                    accounts[i].amount -= obj.wamount;
                    accounts[i].lastacc=time(0);
                    break;
                }
            }
        }
    }
    //Searchs for account when asked by customer/account holder
    bool accfound(int id, int pn)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (id == accounts[i].accno && pn == accounts[i].pin)
            {
                return true;
            }
        }
    }
    //Searches for account when requested by employee
    void Eaccfound(){
        employee obj("data2.txt");
        bool flag=true;
        obj.display_customer();
        for (int i = 0; i < accounts.size(); i++)
        {
            if (obj.search_account == accounts[i].accno)
            {
                cout<<"Account Found!\n";
                flag=false;
            }
        }
        if(flag){
            cout<<"Account Not Found!\n";
        }
    }
    void return_exit()
    {
        return;
    }
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
            f.write((char *)&accounts[i].lastacc, sizeof(accounts[i].lastacc));
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
            f.read((char *)&b.lastacc, sizeof(b.lastacc));
            getline(f, b.branch, '\0');
            accounts.push_back(b);
        }
        f.close();
    }
};

int main()
{
    customer cust("data.txt");
    employee emp("data2.txt");
    emp.load();
    cust.load();
    bool flag = false;
    while (true)
    {
        cout << "\nMessage from developer: if there are no accounts available; create new one using 1. for login details try login as admin and display all accounts\n";
        cout << "WELCOME TO THE BANK OF DREAMING\n";
        cout << "what would you like to do?\n1. CREATE ACCOUNT\n2. LOGIN (USER)\n3. LOGIN (ADMIN)\n4. EXIT\n";
        cout << "Your input: ";
        int option;
        cin >> option;
        cin.ignore();
        bool exit = false;
        bool flags = false;
        switch (option)
        {
        case 1:
            cust.add_account();
            cust.store();
            cout << "Account Added Successfully\n";
            cout<<endl;
            break;
        case 2:

            cout << "LOGIN AS USER\n";
            int account_number;
            cout << "Enter Account Number: ";
            cin >> account_number;
            int pin;
            cout << "Enter Pin: ";
            cin >> pin;
            cout<<endl;
            flags = cust.accfound(account_number, pin);
            if (flags)
            {
                emp.last_entry(account_number);
                emp.store();

                cout << "WELCOME!\n";
                cout << "what would you like to do?\n1. UPDATE ACCOUNT\n2. DEPOSIT\n3. WITHDRAW\n4. SHOW DETAILS\n5.CHECK INTEREST\n6.DELETE ACCOUNT\n7. EXIT\n";
                cout << "Your input: ";
                int option;
                cin >> option;
                cin.ignore();
                switch (option)
                {
                case 1:

                    cust.modify(account_number);
                    cust.store();
                    cout << "Account updated!\n";
                    cout<<endl;
                    break;
                case 2:

                    cust.deposit(account_number, pin);
                    cust.store();
                    cout << "Money deposited!\n";cout<<endl;
                    break;
                case 3:

                    cust.withdraw(account_number, pin);
                    cust.store();cout<<endl;
                    break;
                case 4:

                    cust.c_show_account(account_number);cout<<endl;
                    break;
                case 5:

                    break;
                case 6:

                    cust.delete_account(account_number);
                    cust.store();cout<<endl;
                    break;
                }
            case 7:
                cout<<endl;
                cust.return_exit();
                break;
            }
            break;
        case 3:
        cout<<endl;
            cout << "LOGIN AS ADMIN (password: 123)\n";
            int a_pin;
            cout << "Enter Pin: ";
            cin >> a_pin;
            if (a_pin == 123)
            {

                cout << "WELCOME!\n";
                cout << "what would you like to do?\n1. DISPLAY ALL ACCOUNTS\n2. LAST ENTRY\n3. SEARCH USER\n4. EXIT\n";
                cout << "Your input: ";
                int option;
                cin >> option;
                cin.ignore();
                switch (option)
                {
                case 1:
                    cust.display_all();
                    break;
                case 2:
                    emp.return_entry();
                    break;
                case 3:
                    cust.Eaccfound();
                    break;
                case 4:

                    cust.return_exit();
                    break;
                default:
                    break;
                }
            }

            break;
        case 4:
        cout<<endl;
            exit = true;
            break;
        case 5:
            
            break;
        default:

            break;
        }
        if (exit)
        {
            break;
        }
    }
    return 0;
}