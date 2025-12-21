#pragma once
#include "CliApp.hpp"
#include <vector>
#include <string>
#include <fstream>

struct PService
{
	std::string service;
	std::string username;
	std::string password;
};

class PasswordManager: public CliApp {
public:
	PasswordManager() = default;
	void run_app();
private:
	std::vector<PService> services;
	const std::string file_name = "passwords.db";
	const std::string encryption_key = "!thisisverysecurekey!544231";
	void add_password(std::string& service_name, std::string& username, std::string& password);
	void remove_service(const std::string& service_name);
	PService get_password(const std::string& service_name);
	std::string encrypt_password(std::string& password);
	std::string decrypt_password(const std::string& password);
	void write_file(PService& service);
	void read_file();
};