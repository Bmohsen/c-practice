#include "todo/Todo.hpp"
#include "password-manager/pmanager.hpp"
#include <limits>

using namespace std;

int main()
{
    cout << "Choose application to run:\n";
    while(true) {
        cout << "1. Todo Application\n";
        cout << "2. Passwrod Manager Application\n";
        cout << "3. Press ESC to quit app. \n";
        cout << "Choose: ";

        int ch = _getch();
        if (ch == 27) { // ESC
            system("cls");
            std::exit(0);
        }

        if (ch < '1' || ch > '4') {
            system("cls");
            continue;
        }

        system("cls");

        switch (ch - '0') {
        case 1: {
            Todo todo;
            todo.run_app();
            break;
        }
        case 2: {
            PasswordManager pmanager;
            pmanager.run_app();
            break;
        }
        default:
            break;
        }
	}

}
