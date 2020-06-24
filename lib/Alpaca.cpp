#include "Alpaca.h"
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

std::string Alpaca::_parse_stream_message(alpaca::stream::DataType data)
{
  rapidjson::Document d;
  d.Parse(data.c_str());
  rapidjson::StringBuffer s;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
  d.Accept(writer);
  return s.GetString();
};

std::vector<alpaca::Bar> Alpaca::MarketData_Bars(const std::string symbol)
{
  std::cout << "Retrieving bars for " << symbol << std::endl;
  auto client = alpaca::Client(_env);

  auto bars_response = client.getBars({symbol}, "", "", "", "1Min");

  if (auto status = bars_response.first; !status.ok())
  {
    std::cerr << "Error getting bars information: " << status.getMessage() << std::endl;
    throw status.getCode();
  }
  else
  {
    return bars_response.second.bars[symbol];
  }
}