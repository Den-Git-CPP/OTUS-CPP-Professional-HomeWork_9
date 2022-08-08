#include "InterpreterCmd.h"

bool InterpreterCmd::interpret(const std::string& input, std::string& cmd) {
	if (input.empty()) {
		if ((tokens_ == 0) && (size_ > 0)) {
			size_ = 0;
			return true;
		}
	}
	else if (input == "{") {
		if ((tokens_++ == 0) && (size_ > 0)) {
			size_ = 0;
			return true;
		}
	}
	else if (input == "}") {
		if (tokens_ > 0)
			if (--tokens_ == 0)
				return true;
	}
	else {
		cmd = input;
		if ((tokens_ == 0) && (++size_ == bulk_size_)) {
			size_ = 0;
			return true;
		}
	}
	return false;
}