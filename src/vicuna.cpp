#include "Alpaca.h"
#include "Trade.h"

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Main function, starts traders for each symbol in symbols vector.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char* argv[]) {
  std::vector<std::string> symbols = {"PLUG", "INO", "GNUS", "PENN", "UONE", "WKHS", "LLNW", "NEPT", "SPR",  "MESO",
                                      "TBIO", "JFU", "XRF",  "WINS", "VVNT", "AGLE", "TUFN", "AHCO", "ARGT", "RVMD"};

  auto ap = std::make_shared<Alpaca>();
  std::vector<std::unique_ptr<Trade>> traders;

  std::cout << "Hello! I am Vicuna, your automated trading bot." << std::endl;

  for (std::string symbol : symbols) {
    std::cout << "Creating Trader for " << symbol << std::endl;
    traders.emplace_back(std::make_unique<Trade>(ap, symbol));
  }

  return 0;
}
