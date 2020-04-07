# COVID-19 CLI

This is a simple command line interface written in C++ which gives the count of total cases around the world and India.

###### Requirements

This application requires libcurl to be installed on your system. Run the following command in your terminal to install libcurl.

```
sudo apt-get install libcurl4-openssl-dev
```

###### How to use
Download the code from github, and in the code directory, run the following command to compile the program.

```
g++ -o covid19 -c main.cpp -lcurl
```

Now run the compiled program, to get Covid-19 updates on your terminal.

```
./covid19
```

# Data Sources
[covid19india.org](https://covid19india.org)
[corona-api.com](http://corona-api.com)
