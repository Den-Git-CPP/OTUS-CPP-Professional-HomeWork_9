
#include "WriteConsoler.h"

void WriteConsoler::write(const std::time_t&, const std::vector<std::string>& bulk) {
  os_ << "bulk: ";
  for(const auto &it : bulk) {
    os_ << it << (&it != &bulk.back() ? ", " : "\n");
  }
}

