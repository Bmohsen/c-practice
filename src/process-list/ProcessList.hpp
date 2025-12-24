#pragma once
#include <string>
#include "CliApp.hpp"
#include <unordered_map>
#include <vector>
#include <expected>
#include <Windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <tchar.h>

enum ProcessError {
	PROCESS_NAME_MAX_LEN = 260,
	PROCESS_EMPTY = 0x01,
	PROCESS_ACCESS_DENIED = 0x02,
	PROCESS_NOT_FOUND = 0x03,
	PROCESS_UNKNOWN_ERROR = 0x04
};

struct ProcessInfo {
	int pid;
	std::string name;
};


class TaskManager : public CliApp {
public:
	TaskManager() = default;
	std::vector<ProcessInfo> processes_list = {};
	void run_app();
	std::expected<std::vector<ProcessInfo>, ProcessError> list_processes();
	std::unordered_map<int, size_t> pid_index_map() const;
	void print_processes();
private:
	size_t live_ram_usage();
	size_t live_cpu_usage();
	void process_handle(DWORD processId);
};