#pragma once
#include "CliApp.hpp"
#include <vector>
#include <string>


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
	const char encryption_key = 0x4C;
	void add_password(const std::string& service_name, const std::string& username, const std::string& password);
	void remove_service(const std::string& service_name);
	PService get_password(const std::string& service_name);
	std::string encrypt_password(std::string& password);
	std::string decrypt_password(const std::string& enc_password);
	void write_file(PService& service);
	void read_file();
};