#include <iostream>

#include "alpaca/config.h"
#include "alpaca/streaming.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class Alpaca {
 public:
  Alpaca() {
    // Parse the configuration from the environment
    this->_env = alpaca::Environment();
    if (alpaca::Status status = _env.parse(); !status.ok()) {
      std::cerr << "Error parsing environment: " << status.getMessage() << std::endl;
    } else {
      std::cout << "Environment parsing: " << status.getMessage() << std::endl;
    }
    _start_stream_handler();
  }

 private:
  alpaca::Environment _env;

  std::string _parse_stream_message(alpaca::stream::DataType data);

  void _start_stream_handler() {
    // Log trade updates
    std::function<void(alpaca::stream::DataType data)> on_trade_update = [=](alpaca::stream::DataType data) {
      std::string s = _parse_stream_message(data);
      std::cout << "Got trade update: " << s << std::endl;
    };

    // Log account updates
    std::function<void(alpaca::stream::DataType data)> on_account_update = [=](alpaca::stream::DataType data) {
      std::string s = _parse_stream_message(data);
      std::cout << "Got account update: " << s << std::endl;
    };

    // Create and run the stream handler
    auto handler = alpaca::stream::Handler(on_trade_update, on_account_update);
    if (auto status = handler.run(_env); !status.ok()) {
      std::cerr << "Error running stream handler: " << status.getMessage() << std::endl;
      exit(status.getCode());
    }
  }
};