#include<iostream>
#include<string> 
#include<iomanip>
#include "Bills.h"
#include "customer.h"

using namespace std;

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::left;
using std::right;
using std::fixed;
using std::setw;
using std::ostringstream;


    Bills::Bills(int units,string name,string phoneNo)
    {
        counter++;

        this->numberOfUnits = units;
        if(this->numberOfUnits > 0 && this->numberOfUnits <=100)
        {
            this->unitCost = 2;
        }
        else if(this->numberOfUnits > 100 && this->numberOfUnits <=200)
        {
            this->unitCost = 3;
        }
        else if(this->numberOfUnits > 200 && this->numberOfUnits <=300)
        {
            this->unitCost = 5;
        }
        else
        {
            this->unitCost = 10;
        }
    }

    void Bills::CalculateBill(int cost,int units)
    {
        this->totalBill = this->unitCost*this->numberOfUnits;
    }

    void Bills::DisplayBill()
    {
        ostringstream sout;
        sout.precision(2);
        sout.fill(' ');
        sout<<left<<setw(10)<<Bills::get_Counter<<" ";
        sout.fill(' ');
        sout<<right<<setw(6)<<fixed<<Bills::totalBill;
    }

