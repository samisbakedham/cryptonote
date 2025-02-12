This is the reference code for [Fortress](https://Fortress.org) cryptocurrency protocol.

* Launch your own Fortress currency: [Fortress Starter](https://Fortressstarter.org/)
* Fortress reference implementation: [FortressCoin](https://Fortress-coin.org)
* Discussion board and support: [Fortress Forum](https://forum.Fortress.org)

## Fortress forking how-to

### Preparation

1. Create an account on [GitHub.com](github.com)
2. Fork [Fortress repository](https://github.com/Fortressfoundation/Fortress)
3. Buy one or two Ubuntu-based dedicated servers (at least 2Gb of RAM) for seed nodes.



### First step. Give a name to your coin

**Good name must be unique.** Check uniqueness with [google](http://google.com) and [Map of Coins](mapofcoins.com) or any other similar service.

Name must be specified twice:

**1. in file src/FortressConfig.h** - `Fortress_NAME` constant

Example:
```
const char Fortress_NAME[] = "furiouscoin";
```

**2. in src/CMakeList.txt file** - set_property(TARGET daemon PROPERTY OUTPUT_NAME "YOURCOINNAME**d**")

Example:
```
set_property(TARGET daemon PROPERTY OUTPUT_NAME "furiouscoind")
```

**Note:** You should also change a repository name.


### Second step. Emission logic

**1. Total money supply** (src/FortressConfig.h)

Total amount of coins to be emitted. Most of Fortress based coins use `(uint64_t)(-1)` (equals to 18446744073709551616). You can define number explicitly (for example `UINT64_C(858986905600000000)`).

Example:
```
const uint64_t MONEY_SUPPLY = (uint64_t)(-1);
```

**2. Emission curve** (src/FortressConfig.h)

Be default Fortress provides emission formula with slight decrease of block reward with each block. This is different from Bitcoin where block reward halves every 4 years.

`EMISSION_SPEED_FACTOR` constant defines emission curve slope. This parameter is required to calulate block reward.

Example:
```
const unsigned EMISSION_SPEED_FACTOR = 18;
```

**3. Difficulty target** (src/FortressConfig.h)

Difficulty target is an ideal time period between blocks. In case an average time between blocks becomes less than difficulty target, the difficulty increases. Difficulty target is measured in seconds.

Difficulty target directly influences several aspects of coin's behavior:

- transaction confirmation speed: the longer the time between the blocks is, the slower transaction confirmation is
- emission speed: the longer the time between the blocks is the slower the emission process is
- orphan rate: chains with very fast blocks have greater orphan rate

For most coins difficulty target is 60 or 120 seconds.

Example:
```
const uint64_t DIFFICULTY_TARGET = 120;
```

**4. Block reward formula**

In case you are not satisfied with Fortress default implementation of block reward logic you can also change it. The implementation is in `src/FortressCore/Currency.cpp`:
```
bool Currency::getBlockReward(size_t medianSize, size_t currentBlockSize, uint64_t alreadyGeneratedCoins, uint64_t fee, uint64_t& reward, int64_t& emissionChange) const
```

This function has two parts:

- basic block reward calculation: `uint64_t baseReward = (m_moneySupply - alreadyGeneratedCoins) >> m_emissionSpeedFactor;`
- big block penalty calculation: this is the way Fortress protects the block chain from transaction flooding attacks and preserves opportunities for organic network growth at the same time.

Only the first part of this function is directly related to the emission logic. You can change it the way you want. See MonetaVerde and DuckNote as the examples where this function is modified.


### Third step. Networking

**1. Default ports for P2P and RPC networking** (src/FortressConfig.h)

P2P port is used by daemons to talk to each other through P2P protocol.
RPC port is used by wallet and other programs to talk to daemon.

It's better to choose ports that aren't used by other software or coins. See known TCP ports lists:

* http://www.speedguide.net/ports.php
* http://www.networksorcery.com/enp/protocol/ip/ports00000.htm
* http://keir.net/portlist.html

Example:
```
const int P2P_DEFAULT_PORT = 1478;
const int RPC_DEFAULT_PORT = 8545;
```


**2. Network identifier** (src/P2p/P2pNetworks.h)

This identifier is used in network packages in order not to mix two different cryptocoin networks. Change all the bytes to random values for your network:
```
const static boost::uuids::uuid Fortress_NETWORK = { { 0xA1, 0x1A, 0xA1, 0x1A, 0xA1, 0x0A, 0xA1, 0x0A, 0xA0, 0x1A, 0xA0, 0x1A, 0xA0, 0x1A, 0xA1, 0x1A } };
```


**3. Seed nodes** (src/FortressConfig.h)

Add IP addresses of your seed nodes.

Example:
```
const std::initializer_list<const char*> SEED_NODES = {
  "111.11.11.11:17236",
  "222.22.22.22:17236",
};
```


### Fourth step. Transaction fee and related parameters

**1. Minimum transaction fee** (src/FortressConfig.h)

Zero minimum fee can lead to transaction flooding. Transactions cheaper than the minimum transaction fee wouldn't be accepted by daemons. 100000 value for `MINIMUM_FEE` is usually enough.

Example:
```
const uint64_t MINIMUM_FEE = 100000;
```


**2. Penalty free block size** (src/FortressConfig.h)

Fortress protects chain from tx flooding by reducing block reward for blocks larger than the median block size. However, this rule applies for blocks larger than `Fortress_BLOCK_GRANTED_FULL_REWARD_ZONE` bytes.

Example:
```
const size_t Fortress_BLOCK_GRANTED_FULL_REWARD_ZONE = 20000;
```


### Fifth step. Address prefix

You may choose a letter (in some cases several letters) all the coin's public addresses will start with. It is defined by `Fortress_PUBLIC_ADDRESS_BASE58_PREFIX` constant. Since the rules for address prefixes are nontrivial you may use the [prefix generator tool](https://Fortressstarter.org/tools.html).

Example:
```
const uint64_t Fortress_PUBLIC_ADDRESS_BASE58_PREFIX = 0xe9; // addresses start with "f"
```


### Sixth step. Genesis block

**1. Build the binaries with blank genesis tx hex** (src/FortressConfig.h)

You should leave `const char GENESIS_COINBASE_TX_HEX[]` blank and compile the binaries without it.

Example:
```
const char GENESIS_COINBASE_TX_HEX[] = "";
```


**2. Start the daemon to print out the genesis block**

Run your daemon with `--print-genesis-tx` argument. It will print out the genesis block coinbase transaction hash.

Example:
```
furiouscoind --print-genesis-tx
```


**3. Copy the printed transaction hash** (src/FortressConfig.h)

Copy the tx hash that has been printed by the daemon to `GENESIS_COINBASE_TX_HEX` in `src/FortressConfig.h`

Example:
```
const char GENESIS_COINBASE_TX_HEX[] = "013c01ff0001ffff...785a33d9ebdba68b0";
```


**4. Recompile the binaries**

Recompile everything again. Your coin code is ready now. Make an announcement for the potential users and enjoy!


## Building Fortress

### On *nix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55.

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make`. The resulting executables can be found in `build/release/src`.

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows
Dependencies: MSVC 2013 or later, CMake 2.8.6 or later, and Boost 1.55. You may download them from:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

To build, change to a directory where this file is located, and run theas commands:
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

And then do Build.
Good luck!
