#pragma once
#include <fstream>
#include "StreamWriter.h"
#include "ThreadPool.h"

class WriteFiler : public StreamWriter, public ThreadPool<2> {
  public:
    explicit WriteFiler() : metrics_{"file"} {
    }

    ~WriteFiler() override {
      stop();
    }
    void write(uint8_t context_id, const Bulk& bulk) final;
    Metrics& get_metrics() final;
  
  private:
    std::mutex metrics_mutex_{};
    Metrics metrics_;
};