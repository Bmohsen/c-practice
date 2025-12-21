#include "todo/Todo.hpp"
#include <limits>

using namespace std;

int main()
{
    cout << "Choose application to run:\n";
    while(true) {
        cout << "1. Todo Application\n";
        cout << "2. Passwrod Manager Application\n";
        cout << "Choose: ";
        unsigned int input;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        switch (input)
        {
        case 1: {
            Todo todo;
            todo.run_app();
            break;
        }
        default:
            break;
        }
	}

}
