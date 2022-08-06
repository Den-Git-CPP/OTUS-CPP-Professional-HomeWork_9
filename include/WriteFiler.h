#pragma once
#include <fstream>
#include "StreamWriter.h"

class WriteFiler : public StreamWriter {
  public:
    WriteFiler() = default;
    ~WriteFiler() override = default;
    virtual void write(const std::time_t& time, const std::vector<std::string>& bulk) final;
};


