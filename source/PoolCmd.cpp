#include "PoolCmd.h"
void PoolCmd::push(const std::string& cmd) {
  if(pool_.empty())
    start_bulk_time_ = std::time(nullptr);
  if(!cmd.empty())
    pool_.emplace_back(cmd);
}


