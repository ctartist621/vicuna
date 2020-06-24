#pragma once

#include "Alpaca.h"

#include "alpaca/alpaca.h"
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

enum Timeframe { T1Min, T5Min, T15Min, T1D };

struct History {
  std::vector<alpaca::Bar> _1Min; // 1 Minute bars
  std::vector<alpaca::Bar> _5Min; // 5 Minute Bars
  std::vector<alpaca::Bar> _15Min; // 15 Min Bars
  std::vector<alpaca::Bar> _1D; // 1 Day Bars
};

class StockHistory : public std::enable_shared_from_this<StockHistory> {
 public:
  StockHistory(std::shared_ptr<Alpaca> a, std::string s) : alpaca(a), symbol(s) {
    std::shared_ptr<History> h = std::make_shared<History>(history);
    RetrieveBars(T1Min, h);
    RetrieveBars(T5Min, h);
    RetrieveBars(T15Min, h);
    RetrieveBars(T1D, h);
  }

  ~StockHistory() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
  }

  void RetrieveBars(const Timeframe timeframe, std::shared_ptr<History> history);

  // miscellaneous
  std::shared_ptr<StockHistory> get_shared_this() {
    return shared_from_this();
  }

 private:
  std::shared_ptr<Alpaca> alpaca;
  std::string symbol;
  std::vector<std::thread> threads;
  History history;
};