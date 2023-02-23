#include "../src/graph.c"

#define WIDTH 500 
#define HEIGHT 400 

#define START 500

uint32_t pixels[WIDTH*HEIGHT];

int main() {
    graph_fill_canvas(pixels, WIDTH, HEIGHT, 0xFFFFFFFF);

    graph_draw_line(pixels, WIDTH, HEIGHT, WIDTH/3, 0, WIDTH/3, HEIGHT, 0xFF000000);
    graph_draw_line(pixels, WIDTH, HEIGHT, WIDTH/3*2, 0, WIDTH/3*2, HEIGHT, 0xFF000000);

    graph_draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/3, WIDTH, HEIGHT/3, 0xFF000000);
    graph_draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/3*2, WIDTH, HEIGHT/3*2, 0xFF000000);

    graph_draw_line(pixels, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, 0xFF000000);
    graph_draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT, WIDTH, 0, 0xFF000000);

    graph_draw_line(pixels, WIDTH, HEIGHT, WIDTH/3, HEIGHT/3, WIDTH/3*2, HEIGHT/3*2, 0xFFFF0000);
    graph_draw_line(pixels, WIDTH, HEIGHT, WIDTH/3, HEIGHT/3*2, WIDTH/3*2, HEIGHT/3, 0xFF0000FF);
    
    graph_write_to_ppm_file(pixels, WIDTH, HEIGHT, "imgs/example.ppm");

    return 0;
}
