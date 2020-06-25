#include "StockHistory.h"
#include "Alpaca.h"

#include "alpaca/alpaca.h"
#include <chrono>
#include <memory>
#include <string>

void StockHistory::RetrieveBars(const Timeframe timeframe, std::shared_ptr<History> history) {
  std::string sym = symbol;
  std::shared_ptr<Alpaca> a = alpaca;
  std::shared_ptr<History> h = history;
  auto f = [sym, a, h, timeframe]() {
    while (true) {
      int interval = 60;
      std::string t = "1Min";
      switch (timeframe) {
      case T5Min:
        t = "5Min";
        interval *= 5;
        h->_5Min = a->MarketData_Bars(sym, t);
        break;
      case T15Min:
        t = "15Min";
        interval *= 15;
        h->_5Min = a->MarketData_Bars(sym, t);
        break;
      case T1D:
        t = "1D";
        interval *= 1440;
        h->_1D = a->MarketData_Bars(sym, t);
        break;
      case T1Min:
      default:
        t = "1Min";
        interval = 60;
        h->_1Min = a->MarketData_Bars(sym, t);
        break;
      }

      std::cout << "Retrieving Stock Bars for " << sym << ", " << t << " timeframe every " << interval / 60
                << " minutes" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(interval));
    };
  };

  threads.emplace_back(std::thread(f));
}