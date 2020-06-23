#include "Alpaca.h"
#include <iostream>
#include <string>

std::string Alpaca::_parse_stream_message(alpaca::stream::DataType data) {
  rapidjson::Document d;
  d.Parse(data.c_str());
  rapidjson::StringBuffer s;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
  d.Accept(writer);
  return s.GetString();
};