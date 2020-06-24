#pragma once

#include "alpaca/alpaca.h"
#include "alpaca/config.h"
#include "alpaca/streaming.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <future>
#include <iostream>
#include <thread>
#include <vector>

class Alpaca : public std::enable_shared_from_this<Alpaca> {
 public:
  Alpaca() {
    // Parse the configuration from the environment
    this->_env = alpaca::Environment();
    if (alpaca::Status status = _env.parse(); !status.ok()) {
      std::cerr << "Error parsing environment: " << status.getMessage() << std::endl;
      exit(status.getCode());
    } else {
      std::cout << "Environment parsing: " << status.getMessage() << std::endl;
      threads.emplace_back(std::thread(&Alpaca::start_stream_handler, this));
    }
  }

  ~Alpaca() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
  }

  std::vector<alpaca::Bar> MarketData_Bars(const std::string symbol, const std::string timeframe);

  // miscellaneous
  std::shared_ptr<Alpaca> get_shared_this() {
    return shared_from_this();
  }

 private:
  alpaca::Environment _env;
  std::vector<std::thread> threads;

  std::string _parse_stream_message(alpaca::stream::DataType data);

  void start_stream_handler() {
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