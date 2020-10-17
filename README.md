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

## TODO
- označena pot do videa -> preview ✅
- video mute, če ima dodan audio ✅ + volume
- interaktivno (vrstica z fontom vidiš na levi vse fonte) - autofill ✅ 
- barve (odpre paleto) ✅
- slika/video opcija za crop/fit/fill ✅ 
- velika slika 3d effekt (zoom v sliko počasi) ✅
- github build
