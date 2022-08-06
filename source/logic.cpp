	// while(std::cin) {
	// 	while(0 < _number_commands) {
	// 		std::getline(std::cin, _commands);

	// 		if(std::cin.eof()) {
	// 			break;
	// 		}

	// 		if((_commands != "{") &&
	// 		   (_commands != "}") &&
	// 		   (!_commands.empty())) {
	// 			if(_number_brackets > 0) {
	// 				add_commands();
	// 			}
	// 			else {
	// 				_number_commands--;
	// 				add_commands();
	// 			}
	// 		}

	// 		if(_commands == "{") {
	// 			if((_number_brackets == 0) &&
	// 			   (!_all_commands.empty())
	// 			   ) {
	// 				out_and_clear_bulk();
	// 			}
	// 			_number_brackets++;
	// 		}
	// 		if(_commands == "}") {
	// 			if(_number_brackets <= 0) {
	// 				std::cerr << "Warning: Unexpected bracket\n";
	// 			}
	// 			else {
	// 				_number_brackets--;
	// 				if(_number_brackets <= 0) {
	// 					out_and_clear_bulk();
	// 				}
	// 			}
	// 		}
	// 	}