#pragma once

#include "filters/base_filter.h"

#include <vector>
#include <string>

class Parse {
public:
    Parse(int argc, char** argv);

    std::vector<std::string> GetCommands() const;
    std::string GetFrom() const;
    std::string GetTo() const;

private:
    std::vector<std::string> commands_;
    std::string from_;
    std::string to_;
};