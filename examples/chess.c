#include "../src/graph.c"

#include <stdint.h>

#define SIDE 800
#define GRID_SIZE 8
#define GRID_BLOCK SIDE/GRID_SIZE

uint32_t pixels[SIDE*SIDE];

int main() {
    graph_fill_canvas(pixels, SIDE, SIDE, 0xFFFFFFFF); 
    int divis = 0;
    for(int i = 0; i < SIDE; i+=GRID_BLOCK, divis++) {
        for(int j = 0; j < SIDE; j+=GRID_BLOCK, divis++) {
            if(divis%2==0)
                graph_fill_rectangle(pixels, SIDE, SIDE, i, j, GRID_BLOCK, GRID_BLOCK, 0xFF00A5FF);
        }
    }

    graph_write_to_ppm_file(pixels, SIDE, SIDE, "./imgs/chess.ppm");
    return 0;
}
