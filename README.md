# Vicuna

This is a simple trading bot built on top of [Alpaca](https://alpaca.markets) using the [Bazel](https://www.bazel.build/) build system.

Alpaca is a modern platform for algorithmic trading. You can use the Alpaca API to communicate with Alpaca’s brokerage service. The API allows your trading algorithm to access real-time price data, place orders, maintain watchlists, manage your portfolio, and more. In order to start trading with Alpaca API, please sign up at https://alpaca.markets/.

Bazel is an open-source build and test tool similar to Make, Maven, and Gradle. Bazel supports projects in multiple languages and builds outputs for multiple platforms. Bazel supports large codebases across multiple repositories, and large numbers of users. See the [Bazel Installation Instructions](https://docs.bazel.build/versions/master/install.html) for more information on installing Bazel on your system.

## Defining Envrionment Variables

You will need to define some environment variables for vicuna. These can be sourced by making a free account on the Alpaca website. Consider creating a file called `.env` with content like the following:

```bash
export APCA_API_KEY_ID="<Alpaca API Key ID>"
export APCA_API_SECRET_KEY="<Alpaca API Secret Key>"
export APCA_API_BASE_URL=paper-api.alpaca.markets
export APCA_API_DATA_URL=data.alpaca.markets
```

Then, you can configure this file to be sourced automatically into your shell with a tool like [dotenv](https://github.com/ohmyzsh/ohmyzsh/tree/master/plugins/dotenv) or you can manually `source .env` before running vicuna.

## Building and Running Binaries

If you are in a Udacity workspace, please run `setupWorkspace.sh` first.

You can use Bazel to run vicuna directly!

```
$ bazel run //src:vicuna
```

Or you can build a tool and run it directly:

```
$ bazel build //src:vicuna
$ ./bazel-bin/src/vicuna
```
