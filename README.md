# Simple Video Editor

## Screenshot
![screenshot](https://raw.githubusercontent.com/amadejkastelic/SimpleVideoEditor/develop/res/screenshot.png)

## Building
### Native version
- Build libopenshot-audio and libopenshot (https://github.com/OpenShot/libopenshot/wiki/Linux-Build-Instructions)
- `sudo apt install imagemagick libyaml-cpp-dev libboost-dev`
- `sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json`
- Edit path of libopenshot and libopenshot-audio in CMakeLists.txt to match dir of installed lib (default: `/usr/local/include/libopenshot` and `/usr/local/include/libopenshot-audio`)
- `cmake -B build -S .`
- `cmake --build build`
- `cd build && ./svpeditor`
### AppImage (Ubuntu 16.04)
- `mkdir build && cd build`
- `cmake --build . --config Release`
- `cmake .. -DCMAKE_INSTALL_PREFIX=/usr`
- `make install DESTDIR=AppDir`
- `./linuxdeployqt sveditor.desktop -appimage -bundle-non-qt-libs`

## Usage
The program uses a simple yml syntax.

### Variables
Declare your own custom variables, which you can use later by prefixing it's key with `$`.
```yml
- variables: 
    key: value
    font_position: center
    font_size: 200
    default_path: /path
- part:
    path: $default_path + sample_fhd.mp4
```

### Parts
Each part is a part of the timeline. It must contain some parameters:

- path: absolute or relative (executable location) path to your image/video file (mandatory).
- start: start time of video file in seconds (mandatory if video file).
- end: end time of video file in seconds (mandatory if video file).
- scale: image scale type (CROP, FIT, NONE, STRETCH - mandatory if type=image)
- length: number of seconds to display an image (mandatory if type=image)
- type: type of part/file. (VIDEO/IMAGE, mandatory)
- audio: (optional)
    - path: absolute or relative (executable location) path to your audio file (mandatory).
    - start: start time of audio file in seconds (mandatory).
- text: (optional)
    - part:
        - value: text to display (mandatory)
        - position: position of text (center, bottom, top, left, right, bottom_left, bottom_right, top_left, top_right - mandatory)
        - size: font size in px (mandatory)
        - font: font family (optional)
        - color: hex color (mandatory)
    
### Example
```yml
- variables:
    test: test
    font_position: center
    font_size: 200
    default_path: /home/amadejk/temp/sveditor/
- part:
    path: $default_path + sample_fhd.mp4
    start: 11
    end: 15
    type: VIDEO
    audio:
      path: $default_path + sample.mp3
      start: 11
    text:
      - part:
          value: video test center
          position: $font_position
          size: $font_size
          font: Fira Code
          color: FF85FFA3
      - part:
          value: video test bottom
          position: BOTTOM
          size: 50
          font: Fira Code
          color: FF00AAFF
- part:
    path: $default_path + sample_fhd.jpg
    length: 5
    type: IMAGE
    scale: FIT
    audio:
      path: $default_path + sample.mp3
      start: 21
    text:
      - part:
          value: photo test bottom left
          position: bottom_left
          size: 50
          font: Fira Code
          color: FFFF00FF
```
    
