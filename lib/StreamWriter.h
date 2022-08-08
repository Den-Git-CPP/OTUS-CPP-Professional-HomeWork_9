#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "Bulk.h"
#include "Metrics.h"

class StreamWriter {
  public:
    virtual ~StreamWriter() = default;
    virtual void write(uint8_t context_id, const Bulk& bulk) = 0;
    virtual Metrics& get_metrics() = 0;
};
