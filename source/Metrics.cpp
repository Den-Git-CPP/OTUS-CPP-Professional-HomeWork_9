#include "Metrics.h"

void Metrics::push(const std::thread::id& thread_id, const Bulk& bulk, size_t rows) {
  storage_[thread_id] += MetricsItem{rows, 1, bulk.size()};
}

void Metrics::clear() {
  storage_.clear();
}

std::ostream& operator <<(std::ostream& os, const Metrics& metrics) {
  bool add_thread_num = metrics.storage_.size() > 1;
  size_t thread_num{1};
  for(const auto& it: metrics.storage_) {
    os << metrics.name_;
    if(add_thread_num)
      os << thread_num++;
    os << " thread_id " << it.first << " - ";

    if(it.second.get_rows() > 0)
      os << it.second.get_rows() << " row(s), ";
 
    os << it.second.get_bulks() << " bulk(s), ";
   
    os << it.second.get_cmds() << " command(s) " << std::endl;
  }
  return os;
}


