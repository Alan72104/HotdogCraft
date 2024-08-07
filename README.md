# HotdogCraft
A C++23 Minecraft clone

## Building
### Windows
* Latest Visual Studio with `Desktop development with C++` workload
1. `git clone https://github.com/Alan72104/HotdogCraft`
1. Open folder in VS and let it generate CMake caches
1. Select `x64-Debug` config, `HotdogCraftGame\HotdogCraftGame.exe` target
1. Start without debugging
### WSL Ubuntu 24.04
* G++14 and common windowing/graphics libraries
1. `sudo apt update`
1. `sudo apt install g++-14 cmake make gdb`
1. `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 14`
1. `sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 14`
1. `sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-14 14`
1. `g++ --version` check that the version is at least 14.0
1. `sudo apt install libgl1-mesa-dev libwayland-dev pkg-config libxkbcommon-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev `
1. `git clone https://github.com/Alan72104/HotdogCraft`
1. `cd HotdogCraft`
1. `chmod +x ./build ./run`
1. `./build`
1. `./run`
1. Profit

## Dependencies
* [Exo 2](https://fonts.google.com/specimen/Exo+2) font (Open Font License)
* [CPM](https://github.com/cpm-cmake/CPM.cmake) CMake package manager (MIT)

## License
MIT - [LICENSE.txt](https://github.com/Alan72104/HotdogCraft/blob/master/LICENSE.txt)