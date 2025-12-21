#include "pmanager.hpp"


void PasswordManager::run_app() {

}


void PasswordManager::add_password(std::string& service_name, std::string& username, std::string& password){
	PService service;
	service.service = service_name;
	service.username = username;
	service.password = encrypt_password(password);
	write_file(service);
}

// remove service from vault.db
void PasswordManager::remove_service(const std::string& service_name){
	services.erase(std::remove_if(services.begin(), services.end(), [service_name](const PService& pservice) {
		return pservice.service == service_name;
		}));
	for (auto& service: services) {
		write_file(service);
	}
}


std::string PasswordManager::encrypt_password(std::string& password){
	return "";
}

std::string PasswordManager::decrypt_password(const std::string& password) {
	return "";
}

// write the vault.db file.
void PasswordManager::write_file(PService& service) {
	std::ofstream file("vault.db", std::ios::app);
	if (!file.is_open()) return;
	std::string encrypted_password = encrypt_password(service.password);
	file << service.service << "," << service.username << "," << encrypted_password << "\n";
	file.close();
}

// read the vault.db file.
void PasswordManager::read_file() {
	std::ifstream file("vault.db");
	if (!file.is_open()) return;
	std::string line;
	while (std::getline(file, line)) {
		size_t first_divider = line.find(",");
		size_t second_divider = line.find(",", first_divider + 1);
		if (first_divider == std::string::npos || second_divider == std::string::npos) continue;
		PService service;
		service.service = line.substr(0, first_divider);
		service.username = line.substr(first_divider + 1, second_divider - first_divider - 1);
		service.password = decrypt_password(line.substr(second_divider + 1));
		services.push_back(service);
	}
	file.close();
}