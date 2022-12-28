#include <iostream>
#include <fstream>
#include <chrono>

#include "cca/cca.h"

#define ELAPSED_TIME(MSG, ...) auto start = std::chrono::steady_clock::now(); __VA_ARGS__ ; auto end = std::chrono::steady_clock::now(); std::cout << "Elapsed time in milliseconds [" << MSG << "] : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

int main() {
    const size_t n_images = 10;
    const size_t width = 800, height = 600;

    //open file
    std::ifstream infile("../data/data.bin");

    // get length of file
    infile.seekg(0, std::ios::end);
    std::streamsize length = infile.tellg();
    infile.seekg(0, std::ios::beg);
    auto* buffer = new uint8_t[n_images * height * width];

    // read whole file
    infile.read(reinterpret_cast<char*>(buffer), length);

    auto* result = new uint8_t[n_images * height * width];

    ConnectedComponentAnalysis cca;

    std::ofstream output("../data/results.txt");
    ELAPSED_TIME("Test",
        for(int n = 0; n < n_images; n++){
            std::vector<bbox> boxes = cca.BlobDetection(buffer+n*height*width, result+n*height*width, height, width);
            for (int b = 0; b < boxes.size(); b++){
                output << "(" << boxes[b].y << ", "  << boxes[b].x  << ", "  << boxes[b].h << ", " << boxes[b].w << ") ";
            }
            output << std::endl;
        }
    )
    output.close();

    delete[] result;
    delete[] buffer;
    return 0;
}