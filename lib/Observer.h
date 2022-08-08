#pragma once
#include<memory>
#include "StreamWriter.h"

using observer_t = std::unique_ptr<StreamWriter>;

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void subscribe(observer_t observer) = 0;
    virtual void publish(const Bulk& bulk) = 0;
};


