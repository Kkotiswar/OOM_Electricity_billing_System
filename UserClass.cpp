#include<iostream>
#include<string> 
#include "UserClass.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

 
    int UserClass::counter = 1;
    UserClass::UserClass(string s1,string s2,string s3)
    {   counter++;
        this->User_id = &counter;
        this->userName = s1;
        this->userEmail = s2;
        this->address = s3;
        cout<<"Creating the new instance of the UserClass with name"<<this->userName<<" with id "<<this->User_id<<" and email "<<this->userEmail<<endl;
    }

    void UserClass::deleteUser(UserClass u1)
    {
            if(u1.User_id != NULL)
            {
                delete[] User_id;
                cout<<"Successfully Deleted the selected user"<<endl;
            }
            else
            {
                cout<<"The user that you selected doesnt exist"<<endl;
            }
    }

    void UserClass::editUser(UserClass u1)
    {
            if(u1.User_id != NULL)
            {
                while(1)
                {
                    cout<<"Select what details you want to edit"<<endl;
                    cout<<"1.user name"<<endl;
                    cout<<"2.user email"<<endl;
                    cout<<"3.user name"<<endl;
                    cout<<"4.exit from editing"<<endl;
                    int choice;
                    string newUseremail;
                    string newUserName;
                    string newUserAddress;

                    cin>>choice;
                    switch (choice)
                    {
                    case 1:
                        cout<<"enter the username that you want to change it into"<<endl;
                        cin>>newUserName;
                        u1.userName = newUserName;
                        break;
                    case 2:
                        cout<<"enter the email that you want to change it into"<<endl;
                        cin>>newUseremail;
                        u1.userEmail= newUseremail;
                        break;
                    case 3:
                        cout<<"enter the address that you want to change it into"<<endl;
                        cin>>newUserAddress;
                        u1.address= newUserAddress;
                        break;
                    case 4:
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
