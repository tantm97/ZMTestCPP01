cmake_minimum_required(VERSION 3.0.0)
project( connectedComponentAnalysis )

include_directories(include)

set(CCA_SOURCE
    src/main.cpp
    src/cca.cpp
)

add_executable(blobDetection ${CCA_SOURCE})

