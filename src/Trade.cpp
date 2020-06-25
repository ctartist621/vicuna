#include "Trade.h"

#include <chrono>
#include <string>

double SimpleMovingAverage(std::vector<alpaca::Bar>)
{
}

void Trade::CheckIndicators()
{
  while (true)
  {
    std::vector<alpaca::Bar> history = stockHistory.get1DBars();

    if (history.size() == 0)
    {
      // noop
    }
    else
    {
      std::cout << "CheckIndicators " << symbol << std::endl;
      double sma = SimpleMovingAverage(history);
    }
  }
  std::this_thread::sleep_for(std::chrono::minutes(1));
};