#include "../include/User.hpp"
#include "../include/param.hpp"
#include <stdlib.h>

void User::printUserInfo(void) // for test
{
    cout << "user id(email): " << email << endl;
    cout << "first name: " << first_name << endl;
    cout << "last name: " << last_name << endl;
    cout << "passward: " << passwd << endl;
    cout << "is_admin: " << (is_admin ? "yes" : "no") << endl;
}

void User::init(void)
{
    is_admin = false;
    is_signup = false;
    last_name.clear();
    first_name.clear();
    email.clear();
    passwd.clear();
}

void User::doLogin(void)
{
    bool is_right_input;
    int choice;
    is_right_input = true;
    while (true)
    {
        fflush(stdin);
        fflush(stdout);
        cout << "----< Login menu >" << endl;
        printf("----(1) Login\n");
        printf("----(2) Sign Up\n");
        printf("----(3) Login as Administrator (Manager of Auction System)\n");
        printf("----(4) Quit\n");
        printf("Your choice: ");
        cin >> choice; // integer
        getchar();
        is_admin = false;

        switch (choice)
        {
        case USER_DO_LOGIN_CHOICE_LOGIN_AS_ADMINISTRATOR:
            is_admin = true;
        case USER_DO_LOGIN_CHOICE_LOGIN:
            getLoginInfo();
            break;
        case USER_DO_LOGIN_CHOICE_SIGNUP:
            is_signup = true;
            getSignUpInfo();
            break;
        case USER_DO_LOGIN_CHOICE_QUIT_LOGIN:
            cout << "Bye" << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("error: wrong_input\n");
            is_right_input = false;
            break;
        }

        if (is_right_input)
        {
            break;
        }
    }
}

void User::getLoginInfo(void)
{
    if (is_admin)
        cout << "----< Login as Administrator >" << endl;
    else
        cout << "----< Login >" << endl;

    cout << "enter your ID: "; // string bnam
    cin >> email;
    cout << "enter your password: "; // password
    cin >> passwd;
}

void User::getSignUpInfo(void)
{
    cout << "----< Sign up >" << endl;
    cout << "---- first name: ";
    cin >> first_name;
    cout << "---- last name: ";
    cin >> last_name;
    cout << "---- email: ";
    cin >> email;
    cout << "---- password: ";
    cin >> passwd;
}

void User::getSearchSeller(void)
{
    cout << "enter Seller ID: "; // string bnam
    cin >> email;
}