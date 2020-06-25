
cc_library(
  name = "Alpaca",
  srcs = ["Alpaca.cpp"],
  hdrs = ["Alpaca.h"],
  deps = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "StockHistory",
  srcs = ["StockHistory.cpp"],
  hdrs = ["StockHistory.h"],
  deps = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ":Alpaca",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "Trade",
  srcs = ["Trade.cpp"],
  hdrs = ["Trade.h"],
  deps = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ":Alpaca",
    ":StockHistory",
  ],
  visibility = ["//src:__pkg__"],
)

cc_binary(
  name = "vicuna",
  srcs = ["vicuna.cpp"],
  deps = [
    ":Alpaca",
    ":Trade",
  ],
)