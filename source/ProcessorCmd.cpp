

#include <algorithm>
#include <istream>

#include "ProcessorCmd.h"

void ProcessorCmd::subscribe(const std::shared_ptr<StreamWriter>& observer) {
  auto it = std::find_if(observers_.begin(), observers_.end(), [&observer](observer_t& p) {
      return p.lock() == observer;
  });
  if(it == observers_.end())
    observers_.emplace_back(observer);
}

void ProcessorCmd::unsubscribe(const std::shared_ptr<StreamWriter>& observer) {
  auto it = std::find_if(observers_.begin(), observers_.end(), [&observer](observer_t& p) {
    return p.lock() == observer;
  });
  if(it != observers_.end())
    observers_.erase(it);
}

void ProcessorCmd::process(std::istream& is) {
  for(bool is_eof = false; !is_eof;) {
    std::string input;
    is_eof = !std::getline(is, input);

    std::string cmd;
    bool is_bulk_end = interpreter_.interpret(input, cmd);
    bulk_pool_.push(cmd);
    if(is_bulk_end)
      bulk_pool_.flush(publish);
  }
}


