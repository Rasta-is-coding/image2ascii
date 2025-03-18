#include <stdio.h>
#include <stdlib.h>
#include <colordlg.h>

// Make sure that you have the library file in the same directory as your code is executed
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// This could be adjustable depending on the terminal size
#define aspectRatio 2



// Put the address of your image here guys! :)
// It's better to put the image in the same directory as your code is executed too
// Oh! And one more thing! Try png (with no background) and small images for better results (like less than 100 x 100 px)
const char *path = "C:/Users/Rasta/Desktop/Example/1.png";


// The brightness tolerance converted into characters 
// (The main idea is that the higher the brightness, the more dense the character will be)
char GetSymbolFromBrightness(int brightness) {
    switch (brightness) {
        case 9: return '@';
        case 8: return '$';
        case 7: return '#';
        case 6: return '*';
        case 5: return '!';
        case 4: return '+';
        case 3: return ':';
        case 2: return '~';
        case 1: return '-';
        case 0: return '.';
        default: return ' ';
    }
}


void Draw() {
    int width, height, channels;
    unsigned char *image = stbi_load(path, &width, &height, &channels, 0);
    
    if (!image) {
        printf("Error loading image\n");
        return;
    }
    

    for (int j = 0; j < height; j+=aspectRatio) {
        for (int i = 0; i < width; i++) {
            
            // This fomula is for accessing the pixel indexes
            int pixelIndex = (i + j * width) * channels;

            // Extracting the RGB values from the image! (sounds cool, right? :D)
            unsigned char r = image[pixelIndex];       // Red channel
            unsigned char g = image[pixelIndex + 1];   // Green channel
            unsigned char b = image[pixelIndex + 2];   // Blue channel

            int averageBrightness = (r + g + b) / 3;   // Calculating average brightness
            int scaledBrightness = (averageBrightness * 9) / 255;   //Mapping the average brightness into the scale of 0 to 9

            // Getting corresponding symbol based on brightness
            char symbol = GetSymbolFromBrightness(scaledBrightness);

            printf("%c", symbol);
        }
            printf("\n");
    }

    stbi_image_free(image);  // Free the image memory
}

int main() {
    Draw();
    return 0;
}
