#include <iostream>
#include <sstream>
#include "Logger_in_Console.h"
#include "Logger_in_File.h"
#include "Accumulator_Commands.h"

int main(int argc, char** argv) {
	int number_commands_in_pull{0};
	if(argc <= 1) {
		std::cout << "Incorrect number of arguments";
	}
	else {
		try {
			number_commands_in_pull = std::stoi(argv[1]);
			if(number_commands_in_pull <= 0) {
				std::cout << "Number of commands in bulk must be positive";
			}
		}
		catch(const std::exception& error_command) {
			std::cerr << error_command.what();
		}
	}

	Accumulator_Commands accumulator(number_commands_in_pull);
	Logger_in_Console log_in_console(&accumulator);
	Logger_in_File log_in_file(&accumulator);
	accumulator.work_with_commands();
}
