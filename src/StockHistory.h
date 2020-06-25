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

/**
 * @brief enum of stock timeframes
 *
 */
enum Timeframe { T1Min, T5Min, T15Min, T1D };

/**
 * @brief History struct
 * Holds history for each timeframe for a given stock symbol
 */
struct History {
  std::vector<alpaca::Bar> _1Min; // 1 Minute bars
  std::vector<alpaca::Bar> _5Min; // 5 Minute Bars
  std::vector<alpaca::Bar> _15Min; // 15 Min Bars
  std::vector<alpaca::Bar> _1D; // 1 Day Bars
};

/**
 * @brief Class to encapsulate historical data for a given symbol
 *
 */
class StockHistory : public std::enable_shared_from_this<StockHistory> {
 public:
  /**
   * @brief Construct a new Stock History object
   *
   * @param a
   * @param s
   */
  StockHistory(std::shared_ptr<Alpaca> a, std::string s) : alpaca(a), symbol(s) {
    std::shared_ptr<History> h = std::make_shared<History>(history);
    RetrieveBars(T1Min, h);
    RetrieveBars(T5Min, h);
    RetrieveBars(T15Min, h);
    RetrieveBars(T1D, h);
  }

  /**
   * @brief Destroy the Stock History object
   *
   */
  ~StockHistory() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
  }

  /**
   * @brief 1 Minute Bar getter
   *
   * @return std::vector<alpaca::Bar>
   */
  std::vector<alpaca::Bar> get1MinBars() {
    std::unique_lock<std::mutex> lck(mtx);
    return history._1Min;
  }

  /**
   * @brief 5 Minute Bar getter
   *
   * @return std::vector<alpaca::Bar>
   */
  std::vector<alpaca::Bar> get5MinBars() {
    std::unique_lock<std::mutex> lck(mtx);
    return history._5Min;
  }

  /**
   * @brief 15 Minute Bar getter
   *
   * @return std::vector<alpaca::Bar>
   */
  std::vector<alpaca::Bar> get15MinBars() {
    std::unique_lock<std::mutex> lck(mtx);
    return history._15Min;
  }

  /**
   * @brief 1 Day Bar getter
   *
   * @return std::vector<alpaca::Bar>
   */
  std::vector<alpaca::Bar> get1DBars() {
    std::unique_lock<std::mutex> lck(mtx);
    return history._1D;
  }

  void RetrieveBars(const Timeframe timeframe, std::shared_ptr<History> history);

  // miscellaneous
  /**
   * @brief Get the shared this object
   *
   * @return std::shared_ptr<StockHistory>
   */
  std::shared_ptr<StockHistory> get_shared_this() {
    return shared_from_this();
  }

 private:
  std::shared_ptr<Alpaca> alpaca;
  std::string symbol;
  std::vector<std::thread> threads;
  History history;
  std::mutex mtx;
};