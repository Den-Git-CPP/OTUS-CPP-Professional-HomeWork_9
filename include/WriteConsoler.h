#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include "StreamWriter.h"

class WriteConsoler : public StreamWriter {
  public:
    explicit WriteConsoler(std::ostream& os = std::cout) 
    : os_(os) 
    {}
    ~WriteConsoler() override = default;
    void write(const std::time_t& time, const std::vector<std::string>& bulk) final;

  private:
    std::ostream& os_;
};


