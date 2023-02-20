#ifndef GRAPH_C_
#define GRAPH_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int Errno;

void graph_fill_canvas(uint32_t *pixels, size_t width, size_t height,
                    uint32_t color)
{
    for(size_t i = 0; i < width*height; i++) {
        pixels[i] = color;
    }
}

void graph_fill_rectangle(uint32_t *pixels, size_t width, size_t height,
                        int x0, int y0, int w, int h,
                        uint32_t color)
{
    int dx = x0 + w;
    int dy = y0 + h;
    for(int x = x0; x < dx; x++) {
        if(0 <= x && x <= width) {
            for(int y = y0; y < dy; y++) {
                if(0 <= y && y <= height) {
                    pixels[y*width + x] = color;
                }
            }
        }
    }
}
void graph_fill_circle(uint32_t *pixels, size_t width, size_t height,
                        int xc, int yc, int r,
                        uint32_t color)
{
    for(int x = xc-r; x < xc+r; x++) {
        if(0 <= x && x <= width) {
            for(int y = yc-r; y < yc-r; y++) {
                if(0 <= y && y <= height) {
                    if((x-xc)*(x-xc)+(y-yc)*(y-yc) <= r*r) {
                        pixels[y*width + x] = color;
                    }
                }
            }
        }
    }
}

#define return_defer(v) do{res = (v); goto defer;}while(0)
Errno graph_write_to_ppm_file(uint32_t *pixels, size_t width, size_t height,
                            const char *path)
{
    Errno res = 0;
    FILE *f = fopen(path, "wb");
    if(f == NULL)
        return_defer(-1);

    fprintf(f, "P6\n%zu %zu 255\n", width, height);
    if(ferror(f))
        return_defer(-1);

    for(size_t i = 0; i < width*height; i++) {
        uint32_t pixel = pixels[i];
        uint8_t bytes[3] = {
            (pixel>>8*0)&0xFF,
            (pixel>>8*1)&0xFF,
            (pixel>>8*2)&0xFF,
        };

        fwrite(bytes, sizeof(bytes), 1, f);
        if(ferror(f))
            return_defer(-1);
    }

defer:
    fclose(f);
    return res;
}

#endif /* ifndef GRAPH_C_ */
