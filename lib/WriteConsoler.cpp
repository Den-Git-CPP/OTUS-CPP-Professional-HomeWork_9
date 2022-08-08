#include "WriteConsoler.h"

void WriteConsoler::write(uint8_t, const Bulk& bulk) {
  add_job([this, bulk](){
    os_ << bulk;

    // Добавление метрики.
    std::lock_guard<std::mutex> lock(metrics_mutex_);
    metrics_.push(std::this_thread::get_id(), bulk);
  });
}

Metrics& WriteConsoler::get_metrics() {
  std::lock_guard<std::mutex> lock(metrics_mutex_);
  return metrics_;
}