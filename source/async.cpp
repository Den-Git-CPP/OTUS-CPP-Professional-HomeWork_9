#include "async.h"
#include "ProcessorCmd.h"

namespace async {

handle_t connect(std::size_t bulk_size) {
  return ProcessorCmd::get_instance().create_context(bulk_size);
}

void receive(handle_t handle, const char* data, std::size_t size) {
  ProcessorCmd::get_instance().process(handle, data, size);
}

void disconnect(handle_t handle) {
  return ProcessorCmd::get_instance().destroy_context(handle);
}

}
