#pragma once

#include "Alpaca.h"
#include "StockHistory.h"

#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

class Trade : public std::enable_shared_from_this<Trade> {
 public:
  Trade(std::shared_ptr<Alpaca> a, std::string s) : alpaca(a), symbol(s), stockHistory(a, s) {
    threads.emplace_back(std::thread(&Trade::CheckIndicators, this));
  };

  ~Trade() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
  }

  void CheckIndicators();

  // miscellaneous
  std::shared_ptr<Trade> get_shared_this() {
    return shared_from_this();
  }

 private:
  std::shared_ptr<Alpaca> alpaca;
  std::string symbol;
  StockHistory stockHistory;
  std::vector<std::thread> threads;
};