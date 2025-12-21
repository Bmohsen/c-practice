#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct Item
{
	unsigned int id = 0;
	std::string title;
	std::string description;
};

class Todo {
public:
	std::ofstream db;
	Todo() = default;
	void add(std::string& title, std::string& description);
	void remove(unsigned int id);
	Item get(unsigned int id) const;
	std::vector<Item> list() const;
private:
	void fwrite(const Item& item);
	std::vector<Item> fread() const;
};