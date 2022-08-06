#pragma once

#include <mutex>
#include <set>

#include "ContextCmd.h"
#include "async.h"

class ProcessorCmd  {
  public:
    static ProcessorCmd& get_instance();
    async::handle_t create_context(size_t bulk_size);
    void destroy_context(const async::handle_t& handle);
    void process(const async::handle_t& handle, const char* data, std::size_t size);

  private:
    ProcessorCmd() = default;
    ~ProcessorCmd() = default;

    std::mutex contexts_mutex_{};
    std::map<async::handle_t, std::shared_ptr<ContextCmd>> contexts_;
    uint8_t context_id_{};
};


