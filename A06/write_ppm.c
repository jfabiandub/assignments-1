#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
FILE *fp;
    fp = fopen(filename, "w"); //opens the fille
    if(fp ==NULL){
        printf("Error opening file. %s\n", filename);
        return;
    }
    /*  writes each of the arguments */
    fprintf(fp, "P6 \n");   //type
    fprintf( fp," %d %d\n", w, h);  //width and height
    fprintf(fp, "2555\n");  

    /*  goes through the file and writes the pixels for red, blue and green */
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            fwrite(&pixels[i*w + j].red, 1, 1, fp);
            fwrite(&pixels[i*w + j].blue, 1, 1, fp);
            fwrite(&pixels[i*w + j].green, 1, 1, fp);
        }
    }
    fclose(fp);

}

void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
}
