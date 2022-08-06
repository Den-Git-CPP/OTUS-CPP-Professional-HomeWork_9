#include "Accumulator_Commands.h"

void Accumulator_Commands::add_commands(const std::string& cmd) {
	if (pool_all_commands.empty())
		time_ = std::time(nullptr);
	if (!cmd.empty())
		pool_all_commands.emplace_back(cmd);
}

void Accumulator_Commands::clear_bulk() {
	pool_all_commands.clear();
	time_={};
}

size_t Accumulator_Commands::size() const {
	return pool_all_commands.size();
}

std::time_t Accumulator_Commands::time() const {
	return time_;
}

std::vector<std::string> Accumulator_Commands::get_cmds() const {
	return pool_all_commands;
}

std::ostream& operator<<(std::ostream& os, const Accumulator_Commands& bulk) {
	os << "bulk: ";
	for (const auto& it : bulk.pool_all_commands) {
		os << it << (&it != &bulk.pool_all_commands.back() ? ", " : "\n");
	}
	return os;
}
