#include "pmanager.hpp"


void PasswordManager::run_app() {
	PService service;
	while (true) {
		std::cout << "1-Add Service. \n";
		std::cout << "2-Remove Service. \n";
		std::cout << "3-Get Service \n";
		std::cout << "4-List Services. \n";
		std::cout << "5- Press ESC to return to main menu.";
		std::cout << "Choose: ";

		int ch = _getch();

		// ESC
		if (ch == 27) { 
			system("cls");
			return;
		}

		if (ch < '1' || ch > '4') {
			system("cls");
			continue;
		}

		system("cls");

		switch (ch - '0') 
		{
		case 1:
			std::cout << "Enter Service name: ";
			getline(std::cin, service.service);
			std::cout << "Enter Service username: ";
			getline(std::cin, service.username);
			std::cout << "Enter Service password: ";
			getline(std::cin, service.password);
			add_password(service.service, service.username, service.password);
			break;
		case 2:
			std::cout << "Enter service name to remove: ";
			getline(std::cin, service.service);
			remove_service(service.service);
			break;
		case 3:
			std::cout << "Enter service name to retive: ";
			getline(std::cin, service.username);
			{
				PService s = get_password(service.service);
				std::cout << "Service: " << s.service << "\n";
				std::cout << "Username: " << s.username << "\n";
				std::cout << "Password: " << s.password << "\n";
				std::cout << "---------- \n";
			}
			break;
		case 4:
			read_file();
			for(const auto& s: services){
				std::cout << "Service: " << s.service << "\n";
				std::cout << "username: " << s.username << "\n";
				std::cout << "password: " << s.password << "\n";
				std::cout << "----------- \n";
			}
			break;
		default:
			break;
		}
	}
}


PService PasswordManager::get_password(const std::string& service_name) {
	read_file();
	auto found = std::find_if(services.begin(), services.end(), [&](const PService& s) {
		return s.service == service_name;
		});
	if (found != services.end()) {
		return *found;
	}
	return {};
}

// add a password to a vault
void PasswordManager::add_password(std::string& service_name, std::string& username, std::string& password) {
	PService service;
	service.service = service_name;
	service.username = username;
	service.password = password;
	write_file(service);
}

// remove service from vault.db
void PasswordManager::remove_service(const std::string& service_name) {
	read_file();
	services.erase(std::remove_if(services.begin(), services.end(), [service_name](const PService& pservice) {
		return pservice.service == service_name;
		}));
	std::ofstream("vault.db", std::ios::trunc).close();
	for (auto& service : services) {
		write_file(service);
	}
}


// encrypte simple bitwise operation XOR
std::string PasswordManager::encrypt_password(std::string& password) {
	std::string encrypted = password;
	for (int i = 0; i < password.size(); ++i) {
		encrypted[i] ^= encryption_key;
	}
	return encrypted;
}

// decrypte simple bitwise operation XOR
std::string PasswordManager::decrypt_password(const std::string& enc_password) {
	std::string dec = enc_password;
	for (int i = 0; i < enc_password.size(); ++i) {
		dec[i] ^= encryption_key;
	}
	return dec;
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
	services.clear();
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