#include <iostream>

#include "ProcessorCmd.h"
#include "WriteConsoler.h"
#include "WriteFiler.h"
#include "async.h"

int main(int argc, char const *argv[])
{
    // std::size_t bulk = 5;
    // auto h = async::connect(bulk);
    // auto h2 = async::connect(bulk);
        
    // async::receive(h, "1", 1);
    // async::receive(h2, "1\n", 2);
    // async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    // async::receive(h, "b\nc\nd\n}\n89\n", 11);
    
    // async::disconnect(h);
    // async::disconnect(h2);
 auto bulk_size = std::strtoll(argv[1], nullptr, 0);
   ProcessorCmd cmd_processor(static_cast<size_t>(bulk_size));

  auto file_writer = std::make_shared<WriteFiler>();
  auto console_writer = std::make_shared<WriteConsoler>();

  cmd_processor.subscribe(file_writer);
  cmd_processor.subscribe(console_writer);

  cmd_processor.process(std::cin);

  cmd_processor.unsubscribe(console_writer);
  cmd_processor.unsubscribe(file_writer);


    return 0;
}
