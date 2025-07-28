# Project Donga

## How to setup

Install MinGW prebuild:
    * https://winlibs.com/#download-release
    * winlibs-x86_64-posix-seh-gcc-14.1.0-llvm-18.1.8-mingw-w64ucrt-12.0.0-r3.7z Just unzip to C:\mingw64\
    * g++ --version
    * cmake --version

## How to setup

- [ ] Please run sloppy_build.sh to easy build & run


## How to run manually
Start the server by running:
    ./market_data_server

nc 127.0.0.1 8080
    Each connected client will receive market data updates every 5 seconds.
