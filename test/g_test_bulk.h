#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

class Test_Observer
{
public:
	virtual~Test_Observer() = default;
	virtual void notify(const long long int& time, const std::vector<std::string>& v_stream) = 0;
};

class Test_Accumulator_Commands
{
public:
	Test_Accumulator_Commands(int commands_in_pull)
		: _number_commands_in_pull{commands_in_pull} {
		clear_bulk();
	};
	~Test_Accumulator_Commands() {};

	bool empty();
	void add_commands();
	void clear_bulk();
	void notify_subscriber();
	void out_and_clear_bulk();
	void work_with_commands(const std::vector<std::string>& commands);

	Test_Accumulator_Commands() = default;
	int _number_commands{0};
	int _number_commands_in_pull{0};
	int _number_brackets{0};
	long long int _time_first_command{0};
	std::string _commands{};
	std::vector<std::string> _all_commands;

	void add_subscriber(Test_Observer* ob);
	std::vector<Test_Observer*> subscriber;
};
bool Test_Accumulator_Commands::empty() {
	return _all_commands.empty();
}
void Test_Accumulator_Commands::add_commands() {
	using namespace std::chrono;
	if(empty()) {
		_time_first_command = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	}
	_all_commands.emplace_back(std::move(_commands));
}
void Test_Accumulator_Commands::clear_bulk() {
	_all_commands.clear();
	_number_commands = _number_commands_in_pull;
}
void Test_Accumulator_Commands::out_and_clear_bulk() {
	notify_subscriber();
	clear_bulk();
}
void Test_Accumulator_Commands::work_with_commands(const std::vector<std::string>& commands) {
	for(const auto command : commands) {
		_commands = command; //std::getline(std::cin, _commands);
		if(_commands == "EOF") {//std::cin.eof()
			_number_commands--;
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
void Test_Accumulator_Commands::add_subscriber(Test_Observer* ob) {
	subscriber.push_back(ob);
}
void Test_Accumulator_Commands::notify_subscriber() {

	for(auto elem : subscriber) {
		elem->notify(_time_first_command, _all_commands);
	}
}

class Test_Logger_in_Console: public Test_Observer
{
public:
	Test_Logger_in_Console(Test_Accumulator_Commands* loger) {
		loger->add_subscriber(this);
	}
	~Test_Logger_in_Console() = default;
	long long int _time_first_command{0};
	void notify(const long long int& time_first_command,
				const std::vector<std::string>& v_stream_command);

	Test_Logger_in_Console() = default;
	Test_Logger_in_Console(const Test_Logger_in_Console& root) = delete;
	Test_Logger_in_Console& operator=(const Test_Logger_in_Console&) = delete;
	Test_Logger_in_Console(Test_Logger_in_Console&& root) = delete;
	Test_Logger_in_Console& operator=(Test_Logger_in_Console&&) = delete;
};
void Test_Logger_in_Console::notify(const long long int& time_first_command, const std::vector<std::string>& v_stream_command) {
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
