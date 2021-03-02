#include "parser.h"

int Parser::parseInt(string value, YAML::Node variables) {
    if (value[0] == '$' && variables[value.substr(1)].IsDefined()) {
        return variables[value.substr(1)].as<int>();
    }

    return std::stoi(value);
}

string Parser::parseString(string value, YAML::Node variables) {
    QString text = QString::fromStdString(value);

    if (text.contains("+")) {
        string result;
        QStringList list = text.split("+");
        for (int i = 0; i < list.length(); i++) {
            QString curr = list[i].trimmed();
            if (curr[0] == '$' && variables[curr.toStdString().substr(1)].IsDefined()) {
                result.append(variables[curr.toStdString().substr(1)].as<string>());
            } else {
                result.append(curr.toStdString());
            }
        }

        return result;
    } else if (value[0] == '$' && variables[value.substr(1)].IsDefined()) {
        return variables[value.substr(1)].as<string>();
    }

    return value;
}

vector<spv::File*> Parser::ParseYaml(string yaml) {
    YAML::Node variables;
    YAML::Node instructions = YAML::Load(yaml);
    vector<spv::File*> result;

    if (instructions.IsSequence()) {
        for (auto && instruction : instructions) {
            if (instruction.IsMap() && instruction["part"].IsDefined()) {
                string type = parseString(instruction["part"]["type"].as<string>(), variables);
                string path = parseString(instruction["part"]["path"].as<string>(), variables);
                ScaleType scale = SCALE_NONE;
                vector<Text *> text;

                if (instruction["part"]["scale"].IsDefined()) {
                    QString scaleString = QString::fromStdString(
                            parseString(instruction["part"]["scale"].as<string>(), variables));
                    if (boost::iequals(scaleString.toStdString(), "crop")) {
                        scale = SCALE_CROP;
                    } else if (boost::iequals(scaleString.toStdString(), "fit")) {
                        scale = SCALE_FIT;
                    } else if (boost::iequals(scaleString.toStdString(), "stretch")) {
                        scale = SCALE_STRETCH;
                    } else {
                        scale = SCALE_NONE;
                    }
                }

                YAML::Node labels = instruction["part"]["text"];
                if (labels.IsSequence()) {
                    for (auto && label : labels) {
                        string value = parseString(label["part"]["value"].as<string>(), variables);
                        string position = parseString(label["part"]["position"].as<string>(), variables);
                        string font = parseString(label["part"]["font"].as<string>(), variables);
                        string color = parseString(label["part"]["color"].as<string>(), variables);
                        int size = parseInt(label["part"]["size"].as<string>(), variables);
                        text.push_back(new Text(value, size, font, color, position));
                    }
                }

                if (boost::iequals(type, "video")) {
                    uint start = 0;
                    uint end = 0;
                    if (instruction["part"]["start"].IsDefined()) {
                        start = parseInt(instruction["part"]["start"].as<string>(), variables);
                    }
                    if (instruction["part"]["end"].IsDefined()) {
                        end = parseInt(instruction["part"]["end"].as<string>(), variables);
                    }
                    AudioFile *audio = nullptr;
                    if (instruction["part"]["audio"].IsMap()) {
                        string audioPath = parseString(instruction["part"]["audio"]["path"]
                                .as<string>(), variables);
                        uint audioStart = parseInt(instruction["part"]["audio"]["start"]
                                .as<string>(), variables);
                        audio = new AudioFile(audioPath, audioStart, audioStart + end - start);
                    }
                    result.push_back(new VideoFile(path, start, end, audio, text, scale));
                } else if (boost::iequals(type, "image")) {
                    uint length = parseInt(instruction["part"]["length"].as<string>(), variables);
                    string animation = parseString(instruction["part"]["animation"]
                            .as<string>("none"), variables);
                    AudioFile *audio = nullptr;
                    if (instruction["part"]["audio"].IsMap()) {
                        string audioPath = parseString(instruction["part"]["audio"]["path"]
                                .as<string>(), variables);
                        uint audioStart = parseInt(instruction["part"]["audio"]["start"]
                                .as<string>(), variables);
                        audio = new AudioFile(audioPath, audioStart, audioStart + length);
                    }
                    result.push_back(new ImageFile(path, length, audio, text, scale, animation));
                }
            } else if (instruction.IsMap() && instruction["variables"].IsDefined()) {
                variables = instruction["variables"];
            }
        }
    }

    return result;
}

string Parser::getString(string value, string yaml) {
    YAML::Node variables;
    YAML::Node instructions = YAML::Load(yaml);

    if (instructions.IsSequence()) {
        for (auto &&instruction : instructions) {
            if (instruction.IsMap() && instruction["variables"].IsDefined()) {
                variables = instruction["variables"];
            }
        }
    }

    return Parser::parseString(value, variables);
}
