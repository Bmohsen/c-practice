#include "Todo.hpp"
#include <random>


void Todo::run_app() {
    unsigned int input;
    Todo todo;
    Item item;

    while (true) {
        std::cout << "Todo Application\n";
        std::cout << "1. Add Todo\n";
        std::cout << "2. Remove Todo\n";
        std::cout << "3. Get Todo\n";
        std::cout << "4. List Todos\n";
        std::cout << "Choose: ";

        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls");

        switch (input)
        {
        case 1:
            std::cout << "Enter Title: ";
            getline(std::cin, item.title);

            std::cout << "Enter Description: ";
            getline(std::cin, item.description);

            todo.add(item.title, item.description);
            break;

        case 2: {
            unsigned int id;
            std::cout << "Enter the id to remove: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            todo.remove(id);
            break;
        }

        case 3: {
            unsigned int id;
            std::cout << "Enter id of Todo: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Item found = todo.get(id);
            std::cout << found.title << " - " << found.description << "\n";
            break;
        }

        case 4:
            for (const auto& i : todo.list()) {
                std::cout << "ID: " << i.id << "\n";
                std::cout << "Title: " << i.title << "\n";
                std::cout << "Description: " << i.description << "\n";
                std::cout << "-----------------------\n";
            }
            break;

        default:
            break;
        }
    }
}

// add item to todo list
void Todo::add(std::string& title, std::string& description) {
	Item item;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int random_number = std::rand() % 100000 + 1;
	item.title = title;
	item.description = description;
	item.id = random_number;
	fwrite(item);
}

// remove item from todo
void Todo::remove(unsigned int id){
	std::vector<Item> items = fread();
	items.erase(
		std::remove_if(items.begin(), items.end(),
			[id](const Item& item) {
				return item.id == id;
			}),
		items.end()
	);
	std::ofstream db("db.txt", std::ios::trunc);
	db.close();
	for (const auto& item : items) {
		fwrite(item);
	}
}

// get specefic todo by id from db.txt file
Item Todo::get(unsigned int id) const {
	std::vector<Item> items = list();
	for (const auto& item : items) {
		if (item.id == id) return item;
	}
	return Item{};
}


// return all the todos from db.txt file
std::vector<Item> Todo::list() const {
	std::vector<Item> items = fread();
	if (!items.empty()) return items;
	return items;
}

// write the todo in the db.txt file
void Todo::fwrite(const Item& item) {
	db.open("db.txt", std::ios::app);
	db << item.id << ":" + item.title << "-" << item.description + "\n";
	db.close();
}

// Read all the todos from db.txt files and return Items
std::vector<Item> Todo::fread() const {
	std::vector<Item> items;
	std::ifstream file("db.txt");
	if (!file.is_open()) return items;
	std::string line;
	while(std::getline(file, line)){
		size_t first_colon = line.find(":");
		size_t second_colon = line.find("-", first_colon + 1);
		if (first_colon == std::string::npos || second_colon == std::string::npos) continue;
		Item item;
		item.id = std::stoi(line.substr(0, first_colon));
		item.title = line.substr(first_colon + 1, second_colon - first_colon - 1);
		item.description = line.substr(second_colon + 1);
		items.push_back(item);
	}
	return items;
}