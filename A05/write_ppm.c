#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement one

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
FILE *fp;
    fp = fopen(filename, "w");
    if(fp ==NULL){
        printf("Error opening file. %s\n", filename);
        return;
    }

    fprintf(fp, "P6 \n");
    fprintf( fp," %d %d\n", w, h);
    fprintf(fp, "2555\n");
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            fwrite(&pixels[i*w + j].red, 1, 1, fp);
            fwrite(&pixels[i*w + j].blue, 1, 1, fp);
            fwrite(&pixels[i*w + j].green, 1, 1, fp);
        }
    }
    fclose(fp);

    
}

/*
void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
*/
