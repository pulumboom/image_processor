cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        arg_parser.cpp color.cpp filters/blur.cpp filters/crop.cpp filters/crystallize.cpp filters/edge_detection.cpp filters/grayscale.cpp filters/negative.cpp filters/sharpening.cpp image.cpp image_processor.cpp matrix.cpp
        )
