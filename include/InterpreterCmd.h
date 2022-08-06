#pragma once
#include <string>
class InterpreterCmd {
  public:
    explicit InterpreterCmd(size_t bulk_size) 
    : bulk_size_(bulk_size) 
    {}
    ~InterpreterCmd() = default;
    bool interpret(const std::string& input, std::string& cmd);
  private:
    size_t bulk_size_{};
    size_t size_{};
    size_t tokens_{};
};

