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

##Capstone Project Rubric Requirements
| CRITERIA (15/26)                                                                                 | FILE PATH                           | LINE NUMBERS   | NOTES                                                                                                                                                                                                |
| ------------------------------------------------------------------------------------------------ | ----------------------------------- | -------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **README (3/3)**                                                                                 |
| *A README with instructions is included with the project.*                                       | ./README.md                         | *              |
| *The README indicates which project is chosen.*                                                  | ./README.md                         | 1-11           |
| *The README includes information about each rubric point addressed.*                             | ./README.md                         | 32-65          |
|                                                                                                  |
| **Compiling and Testing (1/1)**                                                                  |
| *The submission must compile and run.*                                                           | ./WORKSPACE                         | *              | I chose bazel as the library I was interfacing with also used bazel.  I took time to make sure there were appropriate setup files for the workspace, and that it compiles and runs in the workspace. |
|                                                                                                  | ./BUILD                             | *              |
| **Loops, Functions, I/O (2/3)**                                                                  |
| *The project demonstrates an understanding of C++ functions and control structures.*             | ./src/Trade.cpp                     | 14, 27, 31     |
| *The project reads data from a file and process the data, or the program writes data to a file.* |                                     |                | While not a file, I chose to implement an SDK around a Trading API.                                                                                                                                  |
| The project accepts user input and processes the input.                                          |
|                                                                                                  |
| **Object Oriented Programming (5/9)**                                                            |
| *The project uses Object Oriented Programming techniques.*                                       | ./src/Trade.h, ./src/StockHistory.h |                | I utilized OOP to organize the data flow I implemented.                                                                                                                                              |
| *Classes use appropriate access specifiers for class members.*                                   | ./src/StockHistory.h                | 65-98          | Getters for different hisstorical timeframes.                                                                                                                                                        |
| *Class constructors utilize member initialization lists.*                                        | ./src/Trade.h                       | 25             |
|                                                                                                  | ./src/StockHistory.h                | 43             |
| *Classes abstract implementation details from their interfaces.*                                 |
| *Classes encapsulate behavior.*                                                                  | ./src/Alpaca.h                      | 24-34          | Encapsulates Alpaca environment parsing                                                                                                                                                              |
|                                                                                                  | ./src/Alpaca.h                      | 67-86          | Encapsulates Alpaca Stream Handler setup                                                                                                                                                             |
| Classes follow an appropriate inheritance hierarchy.                                             |
| Overloaded functions allow the same function to operate on different parameters.                 |
| Derived class functions override virtual base class functions.                                   |
| Templates generalize functions in the project.                                                   |
|                                                                                                  |
| **Memory Management (2/6)**                                                                      |
| The project makes use of references in function declarations.                                    |
| *The project uses destructors appropriately.*                                                    | ./src/Alpaca.h                      | 40-43          |
|                                                                                                  | ./src/Trade.h                       | 33-36          |
|                                                                                                  | ./src/StockHistory.h                | 55-58          |
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.        |
| The project follows the Rule of 5.                                                               |
| The project uses move semantics to move data, instead of copying it, where possible.             |
| *The project uses smart pointers instead of raw pointers.*                                       | ./src/Trade.h                       | 25             |
|                                                                                                  | ./src/StockHistory.h                | 43             |
|                                                                                                  |
| **Concurrency (2/4)**                                                                            |
| *The project uses multithreading.*                                                               | ./src/Alpaca.h                      | 32             |
|                                                                                                  | ./src/Trade.h                       | 26             |
|                                                                                                  | ./src/StockHistory.h                | 51             |
| A promise and future is used in the project.                                                     |
| *A mutex or lock is used in the project.*                                                        | ./src/StockHistory.h                | 66, 76, 86, 96 |
| A condition variable is used in the project.                                                     |

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