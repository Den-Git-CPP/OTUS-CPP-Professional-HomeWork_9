#pragma once
#include <ostream>
#include <string>
#include <map>
#include <thread>

#include "Bulk.h"

class Metrics {
  public:
    explicit Metrics(std::string name) 
    : name_{name}, storage_{}{      
    }
    ~Metrics() = default;
    
    void push(const std::thread::id& thread_id, const Bulk& bulk, size_t rows = 0);
    void clear();
    friend std::ostream& operator <<(std::ostream& os, const Metrics& metrics);

  private:
    class MetricsItem {
      public:
        MetricsItem() = default;
        explicit MetricsItem(size_t rows, size_t bulks, size_t cmds) 
        : rows_{rows}, bulks_{bulks}, cmds_{cmds} {
        }
        ~MetricsItem() = default;

        void operator += (const MetricsItem& other) {
          rows_  += other.rows_;
          bulks_ += other.bulks_;
          cmds_  += other.cmds_;
        }

        size_t get_rows() const {
          return rows_;
        }

        size_t get_bulks() const {
          return bulks_;
        }

        size_t get_cmds() const {
          return cmds_;
        }

      private:
        size_t rows_{};
        size_t bulks_{};
        size_t cmds_{};
    };
    std::string name_;
    std::map<std::thread::id, MetricsItem> storage_;
};

