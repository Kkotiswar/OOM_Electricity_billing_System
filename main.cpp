#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "customer.h"
#include "Bills.h"
#include "userRole.h"
#include "UserClass.h"
#include "methods.h"

using namespace std;

#define SIZE 1000
#define NUMELS 6
#define LSIZE 120

/*getInput: Function to get check input datatype before assigning it*/
template <typename T>
T getInput(T n)
{
    cin >> n;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "\nNot a valid datatype. Please re-enter: ";
        cin >> n;
    }
    return n;
}

float normRate, subsRate;
int count;
ifstream inF;
ofstream outF;

struct bills
{
   string ref;
   string name;
   int cnsmpAmt;
   char subs;
   float bill;
   char paid;
};

struct bills *recsPtr = new bills[SIZE];

//resolve some chars to integers to use as bool
enum
{
    N = 0,
    n = 0,
    out = 0,
    app = 0,
    markp = 1,
    Y = 1,
    y = 1,
    in = 1,
    over = 1,
    del = 2,
    mod = 3
};

int main()
{
    int chc, num;
    cout << R"(
 ___ _   ___ ________ ___ _  ____ _______   __    
| __| | | __/ _/_   _| _ \ |/ _/ |_   _\ `v' /   
| _|| |_| _| \__ | | | v / | \_| | | |  `. .'     
|___|___|___\__/ |_| |_|_\_|\__/_| |_|   !_!     
 __ _ _   _   _ __  _  __    ____   __ __ _____ ___ __ __                 
|  \ | | | | | |  \| |/ _] /' _| `v' /' _/_   _| __|  V  |                
| -< | |_| |_| | | ' | [/\ `._`.`. .'`._`. | | | _|| \_/ |                
|__/_|___|___|_|_|\__|\__/ |___/ !_! |___/ |_| |___|_| |_|                
)" << endl;
    while(1)                       //loop until user closes the program
    {
    cout << "Select an option:\n"
         << "1. Make a new entry\n"
         << "2. View existing entries\n"
         << "3. View/Make changes to billing rates\n"
         << "4. Modify/Delete an entry from the record\n" << endl;
    getRates();
    while(1)                       //loop until valid input is obtained
    {
    chc = getInput(chc);
    if(chc==1)
    {
        newEntry();
        write("billRecs.dat", count, app); //write to file
        cout << "\nEntries appended to file.\n" << endl;
        break;
    }
    else if(chc==2)
    {
        view();
        while(1)
        {
        cout << "1. Search for an entry\n"
             << "2. Mark/Unmark as Paid\n"
             << "0. Go Back\n";
        cin  >> chc;
        if(chc==1)
        {
            cout << "1. Search by Ref. No.\n"
                 << "2. Search by Name\n"
                 << "0. Go Back\n";
            cin  >> chc;
            if(chc==1)
                viewline(search(0));
            else if(chc==2)
                viewline(search(""));
            else if(num==0)
                continue;
        }
        else if(chc==2){
            cout << "\nEnter the Ref. No. of the corresponding record you wish to mark as paid:" << endl;
            num = getInput(num);
            num = search(num);
            if(num==0) //if not found, i.e. return value is 0
                continue;
            modifyEntry(markp, num);
        }
        else if (chc==0)
            break;
        else
            cout << "Invalid choice! Try again\n";
        }
        break;
    }
    else if (chc==3)
    {
        changeRates();
        break;
    }
    else if(chc==4)
    {
        while(1)
        {
        cout << "1. Modify a record\n"
             << "2. Delete a record\n"
             << "0. Go Back\n";
        cin  >> chc;
        if(chc==1)
        {
            cout << "\nEnter the Ref. No. of the corresponding record you wish to modify:" << endl;
            num = getInput(num);
            num = search(num);
            if(num==0)
                continue;
            modifyEntry(mod, num);
        }
        else if(chc==2)
        {
            cout << "\nEnter the Ref. No. of the corresponding record you wish to delete:" << endl;
            num = getInput(num);
            num = search(num);
            if(num==0)
                continue;
            modifyEntry(del, num);
        }
        else if (chc==0)
            break;
        else
            cout << "Invalid choice! Try again\n";
        }
        break;
    }
    else
    {
        cout << "Invalid choice! Try again.\n" << endl;
        continue; //make another iteration
    }
            }
    }
    system("pause");
    return 0;

}

/*newEntry: gets entries from the user and stores in  the array of structs pointed to by recsPtr*/
void newEntry(){
    count = 0;
    cout << "\nEnter the details one by one. If done, enter 'e'.\n";
    for(int n = 0; ; n++) //get entries
    {
        cout << "Ref. No.: ";
        cin  >> (recsPtr + n) -> ref;
        if((recsPtr + n) -> ref=="e")
            break;
        cout << "Customer Name(within \"\"): ";
        cin.ignore();
        getline(cin, (recsPtr + n) -> name);
        cout << "Electricity Consumed (kWh): ";
        cin  >> (recsPtr + n) -> cnsmpAmt;
        cout << "Subsidised(Y/N): ";
        cin  >>  (recsPtr + n) -> subs;
        cout << "Payment Received(Y/N): ";
        cin  >> (recsPtr + n) -> paid;
        if ((recsPtr + n) -> subs)       //change to 'Y' or 'N'
            (recsPtr + n) -> bill = subsRate * (recsPtr + n) -> cnsmpAmt;
        else
            (recsPtr + n) -> bill = normRate * (recsPtr + n) -> cnsmpAmt;
        count++;
    }
}

/*openFile: function to open a file by passing filename as fname
and passing bool value to rw, true for input and false for output*/
int openFile(string fname, bool rw)
{

    inF.open(fname);

    if (!inF)
    {
        cout << "The file " << fname << " could not be located.";
        if(rw)
            return 0;
    }


    if(!rw) //if to be opened for output
    {
        if (!inF)
            cout << " Creating new file...";
        inF.close();
        outF.open(fname, ios_base::app);
    }
    
    return 1;
}

/*getRates: getRates from rates.dat*/
void getRates(){
    openFile("rates.dat", in);
    inF >> normRate >> subsRate;
    inF.close();
}

/*write: appends or overwrites data from the array recs to file fname*/
void write(string fname, int count, bool over)
{
    if(over)
        outF.open(fname); //open to overwrite
    else
        outF.open(fname, ios_base::app); //open to append
    for(int n = 0; n < count; n++)
    {
        outF << fixed << setprecision(2) << left
             << setw(11) << (recsPtr + n) -> ref
             << setw(30) << (recsPtr + n) -> name
             << setw(28) << (recsPtr + n) -> cnsmpAmt
             << setw(14) << (recsPtr + n) -> subs
             << setw(15) << (recsPtr + n) -> bill
             << setw(20) << (recsPtr + n) -> paid << endl;

    }
    outF.close();
}

/*view:  displays the records*/
void view()
{
    string line;
    openFile("billRecs.dat", in);
    header();
    while(inF.good())
    {
        getline(inF, line);
        cout << line << endl;
    }
    inF.close();
}

/*search(): overloaded function to search for Ref No. or Name based on the passed
datatype and return line no*/
int search(int num)
{
    bool found = 0;
    int ref = 0, count = 1, seek = 0;
    if(!openFile("billRecs.dat", in))
        return 0;

    if(num == 0)
    {
        cout << "Enter the Ref. No. of the Customer: ";
        num = getInput(num);
    }

    inF.seekg(seek);

    while(!found)
    {
        inF.seekg(seek);
        inF >> ref;
        if(ref==num){
            found = 1;
            break;
        }
        count++;
        seek += LSIZE;
    }
    inF.close();
    if(found)
        return count;
    else
        cout << "\nRef. No. did not match any records." << endl;
    return 0;
}

/*search(): overloaded function to search for Ref No. or Name based on the passed
datatype and return line no.*/
int search(string str)
{
    bool found = 0;
    int count = 1, seek = 11;
    string name = "";
    if(!openFile("billRecs.dat", in))
        return 0;
    if(str == "")
    {
        cout << "Enter the name of the Customer(case-sensitive): ";
        str = getInput(str);
    }
    while(!found)
    {
        inF.seekg(seek);
        inF >> name;
        if(name==str){
            found = 1;
            break;
        }
        seek += LSIZE;
        count ++;
    }
    inF.close();
    if(found)
        return count;
    else
        cout << "Name did not match any records.";
    return 0;
}

int numline()
{
    int num = 0;
    string line;
    openFile("billRecs.dat", in);
    while(getline(inF, line))
        num++;
    inF.close();
    return num;
}

int rmrn(const char * oldfname, const char * newfname)
{
    int rm, rn;
    rm =  remove(oldfname);
    rn = rename(newfname, oldfname);
    if(rm == 0 && rn == 0)
        return 1;
    else
    {
        cout << "Failure overwriting file!" << endl;
        return 0;
    }
}

void viewline(int lno)
{
    int offset = (lno-1) * LSIZE;
    string line;
    openFile("billRecs.dat", in);
    inF.seekg(offset);
    getline(inF, line);
    inF.close();
    header();
    cout << line << endl;
}

void header()
{
    cout << left
         << setw(11) <<  "Ref. No." 
         << setw(30) <<  "Customer Name"
         << setw(28) <<  "Electricity Consumed(kWh)" 
         << setw(14) <<  "Subsidised"
         << setw(15) <<  "Total Bill" 
         << setw(20) <<  "Payment Received" << endl;
}

void pull(int n)
{
    inF >> (recsPtr + n) -> ref;
    inF >> (recsPtr + n) -> name;
    inF >> (recsPtr + n) -> cnsmpAmt;
    inF >> (recsPtr + n) -> subs;
    inF >> (recsPtr + n) -> bill;
    inF >> (recsPtr + n) -> paid;
}

/*modifyEntry: function to modify entry depending upon the int value of task
where markp = 1 is to mark as paide
del = 2 is to delete
mod = 3 is to modify a line*/
void modifyEntry(int task, int lno)
{
    int n, lines, i = 0;
    lines = numline();
    openFile("billRecs.dat", in);
    inF.seekg(0);
    if (task == 1)
        for(n = 0; (n+1) <= lines; n++)
        {
        pull(n);
        if((n+1) == lno)
            if((recsPtr + n) -> paid == 'Y')
                (recsPtr + n) -> paid = 'N';
            else
                (recsPtr + n) -> paid = 'Y';
        }

    else if (task == 2)
        for(n = 0; (n+1) <= lines; n++)
    {
        if (lno!=(n+1))
        {
            pull(i);
            i++;
        }
        else
            pull(lines);
    }

    else if (task == 3)
        for(n = 0; (n+1) <= lines; n++)
    {
        if (lno!=(n+1))
            pull(n);
        else
        {
            cout << "\nEnter the modified details one by one.\n";
            cout << "Ref. No.: ";
            cin  >> (recsPtr + n) -> ref;
            cout << "Customer Name(w/o space) ";
            cin.ignore();
            getline(cin, (recsPtr + n) -> name);
            cout << "Electricity Consumed (kWh): ";
            cin  >> (recsPtr + n) -> cnsmpAmt;
            cout << "Subsidised(Y/N): ";
            cin  >>  (recsPtr + n) -> subs;
            cout << "Payment Received(Y/N): ";
            cin  >> (recsPtr + n) -> paid;
            if ((recsPtr + n) -> subs)
                (recsPtr + n) -> bill = subsRate * (recsPtr + n) -> cnsmpAmt;
            else
                (recsPtr + n) -> bill = normRate * (recsPtr + n) -> cnsmpAmt;
            pull(lines); //move pointer away from modified line by feeding to unused index
        }
        cout << n;
    }
    inF.close();
    if(task == 1 || task == 3)
        write("billRecsNew.dat", lines, over);
    else if(task == 2)
        write("billRecsNew.dat", (lines - 1), over);
    outF.close();
    if(rmrn("billRecs.dat", "billRecsNew.dat"))
        if(task == 1)
            cout << "\nMarked/Unmarked as Paid\n" << endl;
        else if(task == 2)
            cout << "\nRecord deleted!\n" << endl;
        else if(task == 3)
            cout << "\nRecord modified!\n" << endl;
}

/*changeRates(): function to change rate*/
void changeRates()
{
    int chc;
    float r1, r2;
    string line;
    openFile("rates.dat", in);
    cout << left
         << setw(20) << "\nUnsubsidised Rate"
         << setw(20) << "Subsidised Rate" << endl;
    getline(inF, line);
    cout << line << endl;
    inF.close();
    cout << "\n0. Go back\n"
         << "1. Continue to update rates\n" <<  endl;
    cin  >> chc;
    if(chc!=0)
    {
    cout << "\nEnter new unsubsidised rate: ";
    r1 = getInput(r1);
    cout << "Enter new subsidised rate: ";
    cin  >> r2;
    openFile("rates.dat", out); //check to see if exists
    outF.close();
    outF.open("rates.dat"); //reopen to overwrite
    outF << left
         << setw(20) << r1 
         << setw(20) << r2;
    outF.close();
    cout << "\nRates updated!" << endl;
    }
}