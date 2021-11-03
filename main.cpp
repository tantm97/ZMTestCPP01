#include <iostream>
#include <fstream>

#define ELAPSED_TIME(MSG, ...) auto start = chrono::steady_clock::now(); __VA_ARGS__ ; auto end = chrono::steady_clock::now(); std::cout << "Elapsed time in milliseconds [" << MSG << "] : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

int main() {
    const size_t n_images = 10;
    const size_t width = 800, height = 600;

    //open file
    std::ifstream infile("data.bin");

    // get length of file
    infile.seekg(0, std::ios::end);
    std::streamsize length = infile.tellg();
    infile.seekg(0, std::ios::beg);
    auto* buffer = new char[n_images * height * width];

    // read whole file
    infile.read(buffer, length);


    delete[] buffer;
    return 0;
}
