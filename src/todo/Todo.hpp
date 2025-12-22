#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "CliApp.hpp"

struct Item
{
	unsigned int id = 0;
	std::string title;
	std::string description;
};

class Todo: public CliApp {
public:
	std::ofstream db;
	Todo() = default;
	void add(std::string& title, std::string& description);
	void remove(unsigned int id);
	Item get(unsigned int id) const;
	std::vector<Item> list() const;
	void run_app();
private:
	void fwrite(const Item& item);
	std::vector<Item> fread() const;
};