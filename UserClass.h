#ifndef __User
#define __User

#include<string>
using namespace std;
using std::string;



    class UserClass
    {
        private:
            int* User_id;
            string  userName;
            string userEmail;
            string address;

            static int counter;
        public:
            UserClass(string,string,string);
            void editUser(UserClass);
            void deleteUser(UserClass);
    };


#endif