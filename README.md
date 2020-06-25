# Vicuna

This is a simple trading bot built on top of [Alpaca](https://alpaca.markets) using the [Bazel](https://www.bazel.build/) build system.

Alpaca is a modern platform for algorithmic trading. You can use the Alpaca API to communicate with Alpaca’s brokerage service. The API allows your trading algorithm to access real-time price data, place orders, maintain watchlists, manage your portfolio, and more. In order to start trading with Alpaca API, please sign up at https://alpaca.markets/.

Vicuna runs by creating a Trade Object for each stock symbol being traded.  Within the Trade object, a thread is started to check the stock history periodically for trade signals.  Additionally, within each Trade object, a StockHistory object is instantiated, which in turn runs 4 threads to poll for bar records for the symbol it is designated of tracking.

Both the Trade & Stock History classes take advantage of the Alpaca class, which is instantiated once in the main function and shared through a shared pointer so all requests go through the same instance of the class, allowing for reliable rate limiting (future work) as well as complying with the single subscriber limit to the websocket.

Additional future work involved closing the loop on the trade evaluation, so that the program itself maintains the trades and the portfolio.  Additionally, a GUI is planned, which would run optionally given a command line argument.

## File Structure
```
Vicuna
+-- .env - Environment Variable file (To be added by you)
+-- README.md
+-- WORKSPACE - Bazel build file
+-- setupWorkspace.sh - Script to install environment tools such as bazel
+-- start.sh - Script to source environment variables and run probram
+-- src
|   +-- BUILD - Bazel build file
|   +-- Alpaca.cpp
|   +-- Alpaca.h - Encapsulates all logic around interactions with the Alpaca API & websocket service.
|   +-- StockHistory.cpp
|   +-- StockHistory.h - Stock History class, that encapsulates logic and maintains stock history
|   +-- Trade.cpp
|   +-- Trade.h - Trade class, that handles trade logic functionality
|   +-- vicuna.cpp - Main file, with main function.
```
## Bazel
Bazel is an open-source build and test tool similar to Make, Maven, and Gradle. Bazel supports projects in multiple languages and builds outputs for multiple platforms. Bazel supports large codebases across multiple repositories, and large numbers of users. See the [Bazel Installation Instructions](https://docs.bazel.build/versions/master/install.html) for more information on installing Bazel on your system.

## Defining Environment Variables

You will need to define some environment variables for vicuna. These can be sourced by making a free account on the Alpaca website. Consider creating a file called `.env` with content like the following:

```bash
export APCA_API_KEY_ID="<Alpaca API Key ID>"
export APCA_API_SECRET_KEY="<Alpaca API Secret Key>"
export APCA_API_BASE_URL=paper-api.alpaca.markets
export APCA_API_DATA_URL=data.alpaca.markets
```

Then, you can configure this file to be sourced automatically into your shell with a tool like [dotenv](https://github.com/ohmyzsh/ohmyzsh/tree/master/plugins/dotenv) or you can manually `source .env` before running vicuna.

## Building and Running Binaries

If you are in a Udacity workspace, please run `setupWorkspace.sh` first. Also, I have taken the liberty of populating a `.env` file for you, with an API key against a paper trading account.



You can use Bazel to run Vicuna directly!

```
$ bazel run //src:vicuna
```

Or you can build a tool and run it directly:

```
$ bazel build //src:vicuna
$ ./bazel-bin/src/vicuna
```

Finally, `start.sh` will source the .env and also start the program.