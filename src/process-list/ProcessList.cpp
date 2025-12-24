#include "ProcessList.hpp"
#include <iostream>
#include <conio.h>


void TaskManager::run_app() {
	while (true) {
		std::cout << "1-List Processes. \n";
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
		case 1: {
			TaskManager tsk;
			tsk.print_processes();
			std::cout << "---------- \n";
			break;
		}
		case 2:
			break;
		default:
			break;
		}
	}

}

std::expected<std::vector<ProcessInfo>, ProcessError> TaskManager::list_processes() {
	processes_list.clear();
	// Get the list of process identifiers.
	DWORD processes[1024], cbNeeded, cProcesses;
	unsigned int i;
	if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
		return std::unexpected(ProcessError::PROCESS_UNKNOWN_ERROR);
	}
	// calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++)
	{
		if (processes[i] != 0) {
			process_handle(processes[i]);
		}
	}
	return processes_list;
}

void TaskManager::process_handle(DWORD processId) {
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	// get handle process.
	HANDLE hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId
	);
	// get process name
	if (NULL != hProcess) {
		HMODULE hMode;
		DWORD cbNeeded;
		if (EnumProcessModules(hProcess, &hMode, sizeof(hMode), &cbNeeded)) {
			GetModuleBaseName(hProcess, hMode, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
		}
		CloseHandle(hProcess);
		processes_list.push_back(ProcessInfo{
	static_cast<int>(processId),
	std::string(szProcessName),
			});
	}
	return;
}

void TaskManager::print_processes() {
	auto pList = list_processes();
	if (pList) {
		for (const auto& ps : *pList) {
			std::cout << "PID: " << ps.pid << " Name: " << ps.name << "\n";
		}
	}
	else {
		std::cout << "Error occurred while listing processes: "
			<< static_cast<int>(pList.error()) << "\n";
	}
}


std::unordered_map<int, size_t> TaskManager::pid_index_map() const { std::unordered_map<int, size_t> a;  return a; }

size_t live_ram_usage() { return 1; }
size_t live_cpu_usage() { return 1; }