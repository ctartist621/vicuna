#pragma once

#include "Alpaca.h"

#include "alpaca/alpaca.h"
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex mtx1Min, mtx5Min, mtx15Min, mtx1D;

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

  std::vector<alpaca::Bar> get1MinBars() {
    std::unique_lock<std::mutex> lck(mtx1Min);
    return history._1Min;
  }

  std::vector<alpaca::Bar> get5MinBars() {
    std::unique_lock<std::mutex> lck(mtx5Min);
    return history._5Min;
  }

  std::vector<alpaca::Bar> get15MinBars() {
    std::unique_lock<std::mutex> lck(mtx15Min);
    return history._15Min;
  }

  std::vector<alpaca::Bar> get1DBars() {
    std::unique_lock<std::mutex> lck(mtx1D);
    return history._1D;
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