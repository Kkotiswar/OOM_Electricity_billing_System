#ifndef __Role
#define __ROle
#include "UserClass.h"

using namespace std;
#include<string>
using std::string;


    class userRole : public UserClass
    {
        private:
            int* Role_id;
            string rollTitle;
            string rollDescription;

            static int counter;
        public:
            userRole(string,string,string,string,string,string);
            void editUser(userRole);
            void deleteUser(userRole);
    };

#endif