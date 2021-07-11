#ifndef __BILLS
#define __BILLS

#include "customer.h"
#include<string>

using namespace std;
    class Bills 
    {
    friend class customer;
    private:
        int unitCost;
        int numberOfUnits; 
        float totalBill;
        
        static int counter;
    public:
        Bills(int,string,string);
        int get_Counter()
        {
            return counter;
        }
        void CalculateBill(int,int);
        void DisplayBill();
        ~Bills();
    };


#endif