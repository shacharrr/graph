#ifndef GRAPH_C_
#define GRAPH_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int Errno;

void gmath_swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int gmath_abs(int n) {
    if(n < 0) return -n;
    return n;
}

int gmath_sign(float n) {
    int r = 0;
    if(n > 0.0f)
        r = 1;
    else if(n < 0.0f)
        r = -1;
    return r;
}

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
            for(int y = yc-r; y < yc+r; y++) {
                if(0 <= y && y <= height) {
                    if((x-xc)*(x-xc)+(y-yc)*(y-yc) <= r*r) {
                        pixels[y*width + x] = color;
                    }
                }
            }
        }
    }
}

void graph_draw_line(uint32_t *pixels, size_t width, size_t height,
                    int x1, int y1, int x2, int y2,
                    uint32_t color)
{
    int dx = x2-x1;
    int dy = y2-y1;

    if(dx == 0 && dy == 0) {
        if(0 <= x1 && x1 <= width && 0 <= y1 && y1 <= height) {
            pixels[y1*width+x1] = color;
        }
        return;
    } else if(dx == 0) {
        if(y1 > y2) {
            gmath_swap(&y1, &y2);
        }
        for(int y = y1; y <= y2; y++) {
            pixels[y*width+x1] = color;
        }
        return;
    }

    if(gmath_abs(dx) > gmath_abs(dy)) {
        if(x1 > x2) {
            gmath_swap(&x1, &x2);
            gmath_swap(&y1, &y2);
        }

        if(x1 > width) return;
        if(x2 < 0) return;

        if(x1 < 0) x1 = 0;
        if(x2 >= width) x2 = width-1;

        for(int x = x1; x <= x2; x++) {
            int y = dy*(x - x1)/dx+y1;
            if(0 <= y && y < height) {
                pixels[y*width+x] = color;
            }
        }
    } else {
        if(y1 > y2) {
            gmath_swap(&x1, &x2);
            gmath_swap(&y1, &y2);
        } 

        if(y1 > height) return;
        if(y2 < 0) return;

        if(y1 < 0) y1 = 0;
        if(y2 >= height) y2 = height-1;

        for(int y = y1; y <= y2; y++) {
            int x = dx*(y-y1)/dy+1;
            if(0 <= x && x < width) {
                pixels[y*width+x] = color;
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
