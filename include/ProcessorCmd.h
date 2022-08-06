#pragma once

#include <functional>
#include <list>
#include <memory>

#include "PoolCmd.h"
#include "InterpreterCmd.h"
#include "Observer.h"

class ProcessorCmd : public Observer  {
  public:
    explicit ProcessorCmd(size_t bulk_size) 
    : interpreter_{bulk_size} 
    {}
    ~ProcessorCmd() override = default;
    void subscribe(const std::shared_ptr<StreamWriter>& observer) final;
    void unsubscribe(const std::shared_ptr<StreamWriter>& observer) final;
    void process(std::istream& is);

  private:
    using observer_t = std::weak_ptr<StreamWriter>;
    using publish_t = std::function<void(const std::time_t& bulk_time,
                                         const std::vector<std::string>& cmds)>;
    publish_t publish = [&](const std::time_t& bulk_time,
                            const std::vector<std::string>& bulk) {
      for(auto& it: observers_) {
        if(!it.expired()) {
          auto p = it.lock();
          p->write(bulk_time, bulk);
        }
      }
    };


    std::list<observer_t> observers_{};
    PoolCmd bulk_pool_{};

    InterpreterCmd interpreter_;
};


