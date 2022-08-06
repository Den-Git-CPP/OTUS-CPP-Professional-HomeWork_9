#include "Logger_in_Console.h"

void Logger_in_Console::notify(const long long int& time_first_command, const std::vector<std::string>& v_stream_command) {
	_time_first_command = time_first_command;
	if(!v_stream_command.empty()) {
		std::cout << "\tbulk: ";
		for(size_t i = 0; i < v_stream_command.size(); i++) {
			if(i < v_stream_command.size() - 1) { 
				std::cout << v_stream_command.at(i) << ","; 
			}
			else {
				std::cout << v_stream_command.at(i) << "\n";
			}

		}
		std::cout << '\n';
	}
}
