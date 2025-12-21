#pragma once


class CliApp {
public:
	virtual void run_app() = 0;
	virtual ~CliApp() = default;
};