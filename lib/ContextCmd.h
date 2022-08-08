#pragma once
#include <functional>
#include <list>
#include <memory>
#include <algorithm>
#include <istream>
#include <iostream>
#include <thread>

#include "Bulk.h"
#include "InterpreterCmd.h"
#include "Observer.h"
#include "Metrics.h"

class ContextCmd : public Observer  {
  public:
    explicit ContextCmd(size_t bulk_size, uint8_t id) :
      interpreter_{bulk_size}, metrics_{"main"}, id_{id} {
    }

    ~ContextCmd() override = default;
    void subscribe(observer_t observer) final;
    void process(const char* data, std::size_t size, bool finish_bulk = false);
    void print_metrics(std::ostream& os);

  private:
    void publish(const Bulk& bulk) final;
    std::list<observer_t> observers_{};
    Bulk bulk_{};
    InterpreterCmd interpreter_;
    Metrics metrics_;
    std::string data_;
    uint8_t id_;
};


