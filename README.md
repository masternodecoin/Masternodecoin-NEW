# Masternodecoin

Compile in ubuntu 14.04 or 16.04


## Introduction

A new masternode-enabled cryptocurrency that drives online traffic into a new era of decentralization.

Masternodecoin will serve as the underlying foundation of the blockchain to provide a new source of traffic for the Internet. By using blockchain technology, internet traffic targeting will never be more accurate, and your data will never be owned by anyone.

### Masternode Collateral

500,000

### Block

Block Time: 2 Minutes

Block Size: 2 Megabytes

### Algorithm

NeoScrypt

### Block Rewards

******** blockValue * 70 / 100;

    (nHeight <= 1000 && > 1) {
        nSubsidy = 250 * COIN;
        
    (nHeight < 103680 && nHeight > 1000) {
        nSubsidy = 700 * COIN;
        
    (nHeight < 207360 && nHeight >= 103680) {
        nSubsidy = 600 * COIN;
        
    (nHeight < 311040 && nHeight >= 207360) {
        nSubsidy = 500 * COIN;
        
    (nHeight < 414720 && nHeight >= 311040) {
        nSubsidy = 400 * COIN;
        
    (nHeight < 518400 && nHeight >= 414720) {
        nSubsidy = 350 * COIN;
        
    (nHeight < 622080 && nHeight >= 518400) {
        nSubsidy = 300 * COIN;
        
    (nHeight < 725760 && nHeight >= 622080) {
        nSubsidy = 250 * COIN;
        
    (nHeight < 829440 && nHeight >= 725760) {
        nSubsidy = 200 * COIN;
        
    {nHeight >= 829440
        nSubsidy = 150 * COIN;
        
    }


**Super blocks:**

15 super blocks for every 21600 blocks , reward: 2000



### Ports

+ rpc port=  11185
+ p2p port=  11186
+ Testnet rpc port= 61475   
+ Testnet p2p port = 61474


#### Build client
To build dependencies for the current arch+OS:

    make


To build for another arch/OS:

    make HOST=host-platform-triplet

For example:

    make HOST=x86_64-w64-mingw32 -j4

A prefix will be generated that's suitable for plugging into Bitcoin's
configure. In the above example, a dir named x86_64-w64-mingw32 will be
created. To use it for Bitcoin:

    ./configure --prefix=`pwd`/depends/x86_64-w64-mingw32

Common `host-platform-triplets` for cross compilation are:

- `i686-w64-mingw32` for Win32
- `x86_64-w64-mingw32` for Win64
- `x86_64-apple-darwin11` for MacOSX
- `arm-linux-gnueabihf` for Linux ARM 32 bit
- `aarch64-linux-gnu` for Linux ARM 64 bit

for example
Compile MERCANTE for Windows (64-bit)

./autogen.sh

cd depends

make HOST=x86_64-w64-mingw32 -j4

cd ..

./configure --prefix=`pwd`/depends/x86_64-w64-mingw32 --enable-cxx --disable-shared --enable-static --with-pic

make
