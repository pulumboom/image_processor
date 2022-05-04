#include "arg_parser.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/crystallize.h"
#include "filters/edge_detection.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "image.h"

int main(int argc, char** argv) {
    Parse parse(argc, argv);

    Image img(parse.GetFrom());
    Image result(img);

    std::vector<Filter*> filters;
    for (size_t i = 0; i < parse.GetCommands().size(); ++i) {
        if (parse.GetCommands()[i] == "-crop") {
            filters.push_back(new Crop(std::stoi(parse.GetCommands()[i + 1]), std::stoi(parse.GetCommands()[i + 2])));
            i += 2;
        } else if (parse.GetCommands()[i] == "-gs") {
            filters.push_back(new Grayscale());
        } else if (parse.GetCommands()[i] == "-neg") {
            filters.push_back(new Negative());
        } else if (parse.GetCommands()[i] == "-sharp") {
            filters.push_back(new Sharpening());
        } else if (parse.GetCommands()[i] == "-edge") {
            filters.push_back(new EdgeDetection(std::stod(parse.GetCommands()[i + 1])));
            ++i;
        } else if (parse.GetCommands()[i] == "-blur") {
            filters.push_back(new Blur(std::stod(parse.GetCommands()[i + 1])));
            ++i;
        } else if (parse.GetCommands()[i] == "-crystallize") {
            filters.push_back(new Crystallize(std::stod(parse.GetCommands()[i + 1]))); // param in [0, 1]
            ++i;
        }
    }

    for (const auto& filter : filters) {
        result = filter->Transform(result);
        delete filter;
    }

    result.Save(parse.GetTo());
}
