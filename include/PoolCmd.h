#pragma once

#include <ctime>
#include <string>
#include <vector>

class PoolCmd {
  public:
    PoolCmd() = default;
    ~PoolCmd() = default;
    void push(const std::string& cmd);
    template <typename Pred>
    void flush(Pred pred) {
      if(pred != nullptr)
        pred(start_bulk_time_, pool_);
      pool_.clear();
    }

  private:
    std::vector<std::string> pool_{};
    std::time_t start_bulk_time_{};
};