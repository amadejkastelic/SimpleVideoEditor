#include "parser.h"

vector<spv::File*> Parser::ParseYaml(string yaml) {
    YAML::Node instructions = YAML::Load(yaml);
    vector<spv::File*> result;

    if (instructions.IsSequence()) {
        for (auto && instruction : instructions) {
            if (instruction.IsMap()) {
                string type = instruction["part"]["type"].as<string>();
                string path = instruction["part"]["path"].as<string>();
                ScaleType scale = SCALE_NONE;
                vector<Text *> text;

                if (instruction["part"]["scale"].IsDefined()) {
                    QString scaleString = QString::fromStdString(instruction["part"]["scale"].as<string>()).toUpper();
                    if (scaleString == "CROP") {
                        scale = SCALE_CROP;
                    } else if (scaleString == "FIT") {
                        scale = SCALE_FIT;
                    } else if (scaleString == "STRETCH") {
                        scale = SCALE_STRETCH;
                    } else {
                        scale = SCALE_NONE;
                    }
                }

                YAML::Node labels = instruction["part"]["text"];
                if (labels.IsSequence()) {
                    for (auto && label : labels) {
                        string value = label["part"]["value"].as<string>();
                        string position = label["part"]["position"].as<string>();
                        string font = label["part"]["font"].as<string>();
                        string color = label["part"]["color"].as<string>();
                        uint size = label["part"]["size"].as<uint>();
                        text.push_back(new Text(value, size, font, color, position));
                    }
                }

                if (type == "VIDEO") {
                    uint start = instruction["part"]["start"].as<uint>();
                    uint end = instruction["part"]["end"].as<uint>();
                    AudioFile *audio = nullptr;
                    if (instruction["part"]["audio"].IsMap()) {
                        string audioPath = instruction["part"]["audio"]["path"].as<string>();
                        uint audioStart = instruction["part"]["audio"]["start"].as<uint>();
                        audio = new AudioFile(audioPath, audioStart, audioStart + end - start);
                    }
                    result.push_back(new VideoFile(path, start, end, audio, text, scale));
                } else if (type == "IMAGE") {
                    uint length = instruction["part"]["length"].as<uint>();
                    AudioFile *audio = nullptr;
                    if (instruction["part"]["audio"].IsMap()) {
                        string audioPath = instruction["part"]["audio"]["path"].as<string>();
                        uint audioStart = instruction["part"]["audio"]["start"].as<uint>();
                        audio = new AudioFile(audioPath, audioStart, audioStart + length);
                    }
                    result.push_back(new ImageFile(path, length, audio, text, scale));
                }
            }
        }
    }

    return result;
}
