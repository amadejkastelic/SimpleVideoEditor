# Simple Video Editor

## Screenshot
![screenshot](https://raw.githubusercontent.com/amadejkastelic/SimpleVideoEditor/develop/res/screenshot.png)

## Building
- Build libopenshot-audio and libopenshot (https://github.com/OpenShot/libopenshot/wiki/Linux-Build-Instructions)
- `sudo apt install imagemagick libyaml-cpp-dev libboost-dev`
- `sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json`
- Edit path of libopenshot and libopenshot-audio in CMakeLists.txt to match dir of installed lib (default: `/usr/local/include/libopenshot` and `/usr/local/include/libopenshot-audio`)
- `cmake -B build -S .`
- `cmake --build build`
- `cd build && ./svpeditor`

## Usage
The program uses a simple yml syntax.
- [Example](https://github.com/amadejkastelic/SimpleVideoEditor/blob/master/test.yml)

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
    