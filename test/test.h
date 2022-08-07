#pragma once
#include  "g_test_bulk.h"

TEST(context_test_case, subscribe_test) {
 ContextCmd context{1, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\n";

  context.process(str.c_str(), str.size());

  EXPECT_EQ(TestWriter::get_bulk(), std::vector<std::string>{"cmd1"});
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}


TEST(context_test_case, partial_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n";

  context.process(str.c_str(), str.size());
  context.process(nullptr, 0, true);  

  std::vector<std::string> result{"cmd1", "cmd2"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, full_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\ncmd3\n";

  context.process(str.c_str(), str.size());

  std::vector<std::string> result{"cmd1", "cmd2", "cmd3"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, full_tail_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n";

  context.process(str.c_str(), str.size());
  context.process(nullptr, 0, true);  

  std::vector<std::string> result{"cmd4", "cmd5"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, partial_dyn_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\ncmd6\n";

  context.process(str.c_str(), str.size());

  std::vector<std::string> result{"cmd1", "cmd2"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, full_dyn_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\ncmd6\n}\n";

  context.process(str.c_str(), str.size());

  std::vector<std::string> result{"cmd3", "cmd4", "cmd5", "cmd6"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, full_dyn_bulk_1_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n{\ncmd3\n{\ncmd4\ncmd5\n}\ncmd6\n}\n";

  context.process(str.c_str(), str.size());

  std::vector<std::string> result{"cmd3", "cmd4", "cmd5", "cmd6"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, eof_bulk_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\ncmd6\n}\ncmd7\ncmd8\n";

  context.process(str.c_str(), str.size());
  context.process(nullptr, 0, true);  

  std::vector<std::string> result{"cmd7", "cmd8"};
  EXPECT_EQ(TestWriter::get_bulk(), result);
  EXPECT_NE(TestWriter::get_time(), std::time_t{});
}

TEST(context_test_case, metrics_test) {
 ContextCmd context{3, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\ncmd6\n}\ncmd7\ncmd8\n";

  context.process(str.c_str(), str.size());
  context.process(nullptr, 0, true);  
  std::stringstream ss1;
  ss1 << "test";
  ss1 << " thread_id " << std::this_thread::get_id() << " - ";
  ss1 << 3 << " bulk(s), ";
  ss1 << 8 << " command(s) " << std::endl;

  std::stringstream ss2;
  ss2 <<TestWriter::get_metrics_stub();

  EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(context_test_case, context_id_test) {
 ContextCmd context{1, 1};
  auto test_writer = std::make_unique<TestWriter>();
  context.subscribe(std::move(test_writer));

  std::string str = "cmd1\n";

  context.process(str.c_str(), str.size());

  EXPECT_NE(TestWriter::get_context_id(), 1);
}

TEST(bulk_test_case, print_bulk_test) {
 Bulk bulk;
  bulk.push("cmd1");
  bulk.push("cmd2");
  bulk.push("cmd3");

  std::stringstream ss;
  ss << bulk;

  std::string result{"bulk: cmd1, cmd2, cmd3\n"};

  EXPECT_EQ(ss.str(), result);
}