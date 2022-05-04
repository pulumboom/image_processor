#include "arg_parser.h"

#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "filters/edge_detection.h"

Parse::Parse(int argc, char** argv) {
    if (argc == 0) {
        return;
    }

    std::vector<std::string> args(argv, argv + argc);
    
    from_ = args[1];
    to_ = args[2];

    for (int i = 3; i < argc; ++i) {
        if (args[i] == "-crop") {
            commands_.push_back("-crop");
            commands_.push_back(args[++i]);
            commands_.push_back(args[++i]);
        } else if (args[i] == "-gs") {
            commands_.push_back("-gs");
        } else if (args[i] == "-neg") {
            commands_.push_back("-neg");
        } else if (args[i] == "-sharp") {
            commands_.push_back("-sharp");
        } else if (args[i] == "-edge") {
            commands_.push_back("-edge");
            commands_.push_back(args[++i]);
        } else if (args[i] == "-blur") {
            commands_.push_back("-blur");
            commands_.push_back(args[++i]);
        } else if (args[i] == "-crystallize") {
            commands_.push_back("-crystallize");
            commands_.push_back(args[++i]);
        }
    }
}

std::vector<std::string> Parse::GetCommands() const {
    return commands_;
}

std::string Parse::GetFrom() const {
    return from_;
}

std::string Parse::GetTo() const {
    return to_;
}
