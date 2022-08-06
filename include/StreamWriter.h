#pragma once

#include <ctime>
#include <string>
#include <vector>

class StreamWriter {
  public:
    virtual ~StreamWriter() = default;
    virtual void write(const std::time_t& time, const std::vector<std::string>& bulk) = 0;
};

