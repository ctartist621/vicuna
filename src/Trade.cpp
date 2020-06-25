#include "Trade.h"
#include <chrono>
#include <string>

double SimpleMovingAverage(std::vector<alpaca::Bar> bars)
{
  double sum = 0;
  for (alpaca::Bar b : bars)
  {
    sum += b.close_price;
  }
  return sum / bars.size();
}

void Trade::CheckIndicators()
{
  while (true)
  {
    std::vector<alpaca::Bar> history = stockHistory.get1DBars();

    if (history.size() == 0)
    {
      std::cout << "History not retrieved for " << symbol << ", waiting..." << std::endl;
    }
    else
    {
      std::cout << "CheckIndicators " << symbol << std::endl;
      double sma = SimpleMovingAverage(history);
      std::cout << "SMA: " << sma << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::minutes(1));
  }
};