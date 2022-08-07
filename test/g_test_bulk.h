#pragma once
#include <vector>
#include <string>
#include <sstream>

#include "gtest/gtest.h"
#include "../include/ContextCmd.h"

class TestWriter : public StreamWriter {
  public:
    TestWriter() {
      bulk_pool_.clear();
      metrics_.clear();
      time_ = std::time_t{};
      context_id_ = uint8_t{};
    }

    ~TestWriter() override = default;

    void write(uint8_t context_id, const Bulk& bulk) final {
      bulk_pool_ = bulk.get_cmds();
      time_ = bulk.time();
      metrics_.push(std::this_thread::get_id(), bulk);
      context_id_ = context_id;
    }

    static auto get_bulk() {
      return bulk_pool_;
    }

    static auto get_time() {
      return time_;
    }

    Metrics& get_metrics() final {
      return metrics_;
    }

    static Metrics& get_metrics_stub() {
      return metrics_;
    }

    static auto get_context_id() {
      return time_;
    }

  private:
    static std::vector<std::string> bulk_pool_;
    static std::time_t time_;
    static Metrics metrics_;
    static uint8_t context_id_;
};

std::vector<std::string> TestWriter::bulk_pool_{};
std::time_t TestWriter::time_{};
Metrics TestWriter::metrics_{"test"};
uint8_t TestWriter::context_id_{};

