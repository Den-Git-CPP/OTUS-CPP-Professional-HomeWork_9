#pragma once

#include "StreamWriter.h"

#include<memory>

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void subscribe(const std::shared_ptr<StreamWriter>& observer) = 0;
    virtual void unsubscribe(const std::shared_ptr<StreamWriter>& observer) = 0;
};
