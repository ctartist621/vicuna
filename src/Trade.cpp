#include "Trade.h"
#include <chrono>
#include <string>

/**
 * @brief Calculates a Simple Moving average from the returned closing prices
 * 
 * @param bars 
 * @return double 
 */
double SimpleMovingAverage(std::vector<alpaca::Bar> bars)
{
  double sum = 0;
  for (alpaca::Bar b : bars)
  {
    sum += b.close_price;
  }
  return sum / bars.size();
}

/**
 * @brief Calculates various technical indicators, and returns a BUY, HOLD, or SELL decision
 * 
 */
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