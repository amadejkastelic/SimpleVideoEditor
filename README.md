# Simple Video Editor
## Building
- Build libopenshot-audio and libopenshot (https://github.com/OpenShot/libopenshot/wiki/Linux-Build-Instructions)
- `sudo apt install imagemagick libyaml-cpp-dev libboost-dev`
- `sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json`
- Edit path of libopenshot and libopenshot-audio in CMakeLists.txt to match dir of installed lib (default: `/usr/local/include/libopenshot` and `/usr/local/include/libopenshot-audio`)
- `cmake -B build -S .`
- `cmake --build build`
- `cd build && ./svpeditor`

## Usage
- [Example](https://github.com/amadejkastelic/SimpleVideoEditor/blob/master/test.yml)
- TODO: attribute description