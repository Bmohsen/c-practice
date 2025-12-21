#include "todo.h"
#include <limits>

using namespace std;

int main()
{
    unsigned int input;
    Todo todo;
    Item item;

    while (true) {
        cout << "Todo Application\n";
        cout << "1. Add Todo\n";
        cout << "2. Remove Todo\n";
        cout << "3. Get Todo\n";
        cout << "4. List Todos\n";
        cout << "Choose: ";

        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");

        switch (input)
        {
        case 1:
            cout << "Enter Title: ";
            getline(cin, item.title);

            cout << "Enter Description: ";
            getline(cin, item.description);

            todo.add(item.title, item.description);
            break;

        case 2: {
            unsigned int id;
            cout << "Enter the id to remove: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            todo.remove(id);
            break;
        }

        case 3: {
            unsigned int id;
            cout << "Enter id of Todo: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Item found = todo.get(id);
            cout << found.title << " - " << found.description << "\n";
            break;
        }

        case 4:
            for (const auto& i : todo.list()) {
                cout << "ID: " << i.id << "\n";
                cout << "Title: " << i.title << "\n";
                cout << "Description: " << i.description << "\n";
                cout << "-----------------------\n";
            }
            break;

        default:
            break;
        }
    }
}
