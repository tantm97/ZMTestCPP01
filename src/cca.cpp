#include "cca/cca.h"

ConnectedComponentAnalysis::ConnectedComponentAnalysis(){

}

ConnectedComponentAnalysis::~ConnectedComponentAnalysis(){

}

std::vector<bbox> ConnectedComponentAnalysis::BlobDetection(uint8_t* source, uint8_t* labels, int height, int width){
    int region = 1;
    // contiguous existence or not?
    bool has_vertex = false;
    std::vector<bbox> boxes;

    // use Depth First Search to explore the connected component.
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (labels[i*width+j] == 0 and source[i*width+j] > 0){
                int xmin = 0, ymin = 0, xmax = width-1, ymax = height-1;
                if (j > xmin)  xmin = j;
                if (j < xmax)  xmax = j;
                if (i > ymin)  ymin = i;
                if (i < ymax)  ymax = i;

                // push position of this pixel to stack
                std::stack<std::pair<int, int> > s;
                s.push(std::make_pair(i, j));
                // assign value for region.
                labels[i*width+j] = region;

                while (!s.empty()){
                    // get value from stack.
                    int vertex_y = s.top().first;
                    int vertex_x = s.top().second;

                    // browse adjacent vertices that have not yet been traversed.
                    for (int coor = 0; coor < 8; coor++){
                        int next_vertex_y = vertex_y + dy[coor];
                        int next_vertex_x = vertex_x + dx[coor];
                        if (next_vertex_x >= 0 && next_vertex_x < width && next_vertex_y >= 0 && next_vertex_y < height 
                            && labels[next_vertex_y*width+next_vertex_x] == 0 
                            && source[next_vertex_y*width+next_vertex_x] > 0){

                            // Update new value for bouding box
                            if (next_vertex_x < xmin)  xmin=next_vertex_x;
                            if (next_vertex_x > xmax)  xmax=next_vertex_x;
                            if (next_vertex_y < ymin)  ymin=next_vertex_y;
                            if (next_vertex_y > ymax)  ymax=next_vertex_y;

                            // assign value for region and push to stack
                            labels[next_vertex_y*width+next_vertex_x] = region;
                            s.push(std::make_pair(next_vertex_y, next_vertex_x));

                            // contiguous existence.
                            has_vertex = true;
                            break;
                        }
                    }
                    
                    // remove vertex from stack if there is no adjacent vertex.
                    if (!has_vertex) s.pop();
                    has_vertex = false;
                }

                // push coordinates of bounding box to vector
                bbox box;
                box.x = xmin;
                box.y = ymin;
                box.w = xmax - xmin + 1;
                box.h = ymax - ymin + 1;
                boxes.push_back(box);

                // increase value for the next connected component.
                region++;
            }
        }
    }
    return boxes;
}