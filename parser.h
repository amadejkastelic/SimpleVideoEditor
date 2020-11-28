#pragma once

#include "yaml-cpp/yaml.h"
#include <iostream>
#include "data/image_file.h"
#include "data/video_file.h"
#include <boost/algorithm/string/predicate.hpp>

class Parser {

public:
    static vector<spv::File*> ParseYaml(string yaml);

private:
    static int parseInt(string value, YAML::Node variables);
    static string parseString(string value, YAML::Node variables);
};
