#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include "StreamWriter.h"
#include "ThreadPool.h"

class WriteConsoler : public StreamWriter, public ThreadPool<> {
  public:
    explicit WriteConsoler(std::ostream& os = std::cout) : os_(os), metrics_{"log"} {
    }

    ~WriteConsoler() override {
      stop();
    }
    void write(uint8_t context_id, const Bulk& bulk) final;
    Metrics& get_metrics() final;

  private:
    std::ostream& os_;
    std::mutex metrics_mutex_{};
    Metrics metrics_;
};