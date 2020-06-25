#pragma once

#include "Alpaca.h"
#include "StockHistory.h"

#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

/**
 * @brief Trade Class
 * Contains all logic regarding whether or not to place a trade.
 */
class Trade : public std::enable_shared_from_this<Trade> {
 public:
  /**
   * @brief Construct a new Trade object
   *
   * @param a
   * @param s
   */
  Trade(std::shared_ptr<Alpaca> a, std::string s) : alpaca(a), symbol(s), stockHistory(a, s) {
    threads.emplace_back(std::thread(&Trade::CheckIndicators, this));
  };

  /**
   * @brief Destroy the Trade object
   *
   */
  ~Trade() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
  }

  void CheckIndicators();

  // miscellaneous
  /**
   * @brief Get the shared this object
   *
   * @return std::shared_ptr<Trade>
   */
  std::shared_ptr<Trade> get_shared_this() {
    return shared_from_this();
  }

 private:
  std::shared_ptr<Alpaca> alpaca;
  std::string symbol;
  StockHistory stockHistory;
  std::vector<std::thread> threads;
};