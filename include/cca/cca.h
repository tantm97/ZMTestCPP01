#ifndef CONNECTED_COMPONENT_ANALYSIS_H_
#define CONNECTED_COMPONENT_ANALYSIS_H_

#include <iostream>
#include <stack>
#include <vector>

// Bouding box
struct bbox {
    int x;
    int y;
    int h;
    int w;
};


class ConnectedComponentAnalysis {
    public:
        ConnectedComponentAnalysis();

        std::vector<bbox> BlobDetection(uint8_t* source, uint8_t* labels, int height, int width);

        ~ConnectedComponentAnalysis();

    private:
        const int dy[8] = {-1, -1, -1, +0, +0, +1, +1, +1};
        const int dx[8] = {-1, +0, +1, -1, +1, -1, +0, +1};
};

#endif  // CONNECTED_COMPONENT_ANALYSIS_H_
