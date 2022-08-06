#include "Accumulator_Commands.h"

bool Accumulator_Commands::empty() {
	return _all_commands.empty();
}

void Accumulator_Commands::add_commands() {
	using namespace std::chrono;
	if(empty()) {
		_time_first_command = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	}
	_all_commands.emplace_back(std::move(_commands));
}

void Accumulator_Commands::clear_bulk() {
	_all_commands.clear();
	_number_commands = _number_commands_in_pull;
}

void Accumulator_Commands::out_and_clear_bulk() {
	notify_subscriber();
	clear_bulk();
}

void Accumulator_Commands::work_with_commands() {

	while(std::cin) {
		while(0 < _number_commands) {
			std::getline(std::cin, _commands);

			if(std::cin.eof()) {
				break;
			}

			if((_commands != "{") &&
			   (_commands != "}") &&
			   (!_commands.empty())) {
				if(_number_brackets > 0) {
					add_commands();
				}
				else {
					_number_commands--;
					add_commands();
				}
			}

			if(_commands == "{") {
				if((_number_brackets == 0) &&
				   (!_all_commands.empty())
				   ) {
					out_and_clear_bulk();
				}
				_number_brackets++;
			}
			if(_commands == "}") {
				if(_number_brackets <= 0) {
					std::cerr << "Warning: Unexpected bracket\n";
				}
				else {
					_number_brackets--;
					if(_number_brackets <= 0) {
						out_and_clear_bulk();
					}
				}
			}
		}

		if(_number_brackets == 0) {
			out_and_clear_bulk();
		}
	}
}

void Accumulator_Commands::add_subscriber(Observer* obs) {
	subscriber.push_back(obs);
}

void Accumulator_Commands::remove_subscriber() {
	subscriber.clear();
}

void Accumulator_Commands::notify_subscriber() {
	for(auto elem : subscriber) {
		elem->notify(_time_first_command, _all_commands);
	}
}
