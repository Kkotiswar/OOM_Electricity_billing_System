#include<iostream>
#include<string>
#include "userRole.h"
#include "UserClass.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

namespace bill
{   
    int userRole::counter = 1;
    userRole::userRole(string ss1,string ss2,string ss3,string s1,string s2,string s3) : UserClass(ss1,ss2,ss3)
    {   counter++;
        this->Role_id = &counter;
        this->rollTitle = s1;
        this->rollDescription = s3;
        cout<<"Creating the new instance of the userRole with name"<<this->rollTitle<<" with id "<<this->Role_id<<" and roll description "<<this->rollDescription<<endl;
    }

    void userRole::deleteUser(userRole u1)
    {
            if(u1.Role_id != NULL)
            {
                delete[] Role_id;
                cout<<"Successfully Deleted the selected user Role"<<endl;
            }
            else
            {
                cout<<"The user role that you selected doesnt exist"<<endl;
            }
    }

    void userRole::editUser(userRole u1)
    {
            if(u1.Role_id != NULL)
            {
                while(1)
                {
                    cout<<"Select what details you want to edit"<<endl;
                    cout<<"1.user Title"<<endl;
                    cout<<"2.user Title Description"<<endl;
                    cout<<"3.exit from editing"<<endl;
                    int choice;
                    string newrollTitle;
                    string newUserrollDescription;

                    cin>>choice;
                    switch (choice)
                    {
                    case 1:
                        cout<<"enter the rollTitle that you want to change it into"<<endl;
                        cin>>newrollTitle;
                        u1.rollTitle = newrollTitle;
                        break;
                    case 2:
                        cout<<"enter the rollDescription that you want to change it into"<<endl;
                        cin>>newUserrollDescription;
                        u1.rollDescription= newUserrollDescription;
                        break;
                    case 3:
                        cout<<"Successfully Deleted the selected user"<<endl;
                        cout<<"exiting from editing"<<endl;
                        exit(0);
                        break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                cout<<"The user that you selected doesnt exist"<<endl;
            }
        
        
    }
}