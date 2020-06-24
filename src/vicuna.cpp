#include "../lib/Alpaca.h"
#include <iostream>

int main(int argc, char *argv[])
{
  std::vector<std::string> symbols = {
      "PLUG",
      "INO",
      "GNUS",
      "PENN",
      "UONE",
      "WKHS",
      "LLNW",
      "NEPT",
      "SPR",
      "MESO",
      "TBIO",
      "JFU",
      "XRF",
      "WINS",
      "VVNT",
      "AGLE",
      "TUFN",
      "AHCO",
      "ARGT",
      "RVMD",
  };

  std::cout << "Hello! I am Vicuna, your automated trading bot." << std::endl;
  Alpaca a;
  std::vector<alpaca::Bar> AAPL = a.MarketData_Bars("AAPL");

  for(alpaca::Bar a : AAPL) {
    std::cout << "AAPL: " << a.close_price << std::endl;

  }

  return 0;
}