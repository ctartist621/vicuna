sudo apt install -y curl gnupg

sudo apt-get install -y openjdk-8-jdk

sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update -y && sudo apt-get install -y oracle-java8-installer

echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -

sudo apt-get update -y && sudo apt-get install -y bazel
sudo apt-get upgrade -y bazel

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update
sudo apt-get install g++-7
