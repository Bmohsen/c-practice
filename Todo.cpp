#include "Todo.hpp"
#include <random>


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