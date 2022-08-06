#pragma once
#include  "g_test_bulk.h"

TEST(Test_Logger_in_Console, create_and_subscribe) {
	 Test_Accumulator_Commands acc_commands(3);
	 Test_Logger_in_Console log_in_console(&acc_commands);

	 EXPECT_EQ(acc_commands.subscriber.size(), 1);
}

TEST(Test_Accumulator_Commands, work_with_commands_without_brackets) {
	/*Test cmd1,cmd2,cmd3
	*/
	std::vector<std::string> commands{"cmd1","cmd2","cmd3"};
	Test_Accumulator_Commands test_acc_commands(static_cast<int>(commands.size()));
	Test_Logger_in_Console log_in_console(&test_acc_commands);
	std::stringstream buffer, strm;
	strm << "\tbulk: cmd1,cmd2,cmd3\n\n";
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	test_acc_commands.work_with_commands(commands);

	std::cout.rdbuf(sbuf);
	EXPECT_EQ(buffer.str(), strm.str());
	EXPECT_EQ(test_acc_commands._all_commands.size(), 0);
}
TEST(Test_Accumulator_Commands, work_with_commands_EOF) {
	/*Test cmd1,cmd2,EOF
	*/
	std::vector<std::string> commands{"cmd4","cmd5","EOF"};
	Test_Accumulator_Commands test_acc_commands(static_cast<int>(commands.size()));
	Test_Logger_in_Console log_in_console(&test_acc_commands);
	std::stringstream buffer, strm;
	strm << "\tbulk: cmd4,cmd5\n\n";
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	test_acc_commands.work_with_commands(commands);

	std::cout.rdbuf(sbuf);
	EXPECT_EQ(buffer.str(), strm.str());
	EXPECT_EQ(test_acc_commands._all_commands.size(), 0);
}
TEST(Test_Accumulator_Commands, work_with_commands_brackets) {
	/*Test cmd1,cmd2 {
	*      cmd3,cmd4 }
	*/
	std::vector<std::string> commands{"cmd1","cmd2","{",
									   "cmd3","cmd4","}"
									 };

	Test_Accumulator_Commands test_acc_commands(static_cast<int>(commands.size()));
	Test_Logger_in_Console log_in_console(&test_acc_commands);
	std::stringstream buffer, strm;
	strm << "\tbulk: cmd1,cmd2\n\n"
		 << "\tbulk: cmd3,cmd4\n\n";
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	test_acc_commands.work_with_commands(commands);
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(buffer.str(), strm.str());
	EXPECT_EQ(test_acc_commands._all_commands.size(), 0);
}
TEST(Test_Accumulator_Commands, work_with_all_commands) {
	/*Test all commands
	*/
	std::vector<std::string> commands{
		"cmd1","cmd2", "{",
		"cmd3", "cmd4","}",
		"{",
		"cmd5","cmd6",
		"{",
		"cmd7","cmd8",
		"}",
		"cmd9",
		"}"
	};

	Test_Accumulator_Commands test_acc_commands(static_cast<int>(commands.size()));
	Test_Logger_in_Console log_in_console(&test_acc_commands);
	std::stringstream buffer, strm;
	strm << "\tbulk: cmd1,cmd2\n\n"
		<< "\tbulk: cmd3,cmd4\n\n"
		<< "\tbulk: cmd5,cmd6,cmd7,cmd8,cmd9\n\n";
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	test_acc_commands.work_with_commands(commands);
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(buffer.str(), strm.str());
	EXPECT_EQ(test_acc_commands._all_commands.size(), 0);
}
