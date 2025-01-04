#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esp_log.h"
#include "nvs_flash.h"
#include "FreeMono9pt7b.h"

static const char *TAG = "Font";


int counter = 0;
int counterHeight = 0;
int counterByte = 0;

void printBinary(unsigned char value, int length, int height) {
    //ESP_LOGI(TAG, "\nCounter: %d Byte: %.4x\n", counterByte, value);
    //counterByte++;
    for (int i = 7; i >= 0; i--) {
        if(counterHeight==height){
            continue;
        }
        printf("%d", (value >> i) & 1);
        counter++;
        if(counter==length){
            printf("\n");
            counterHeight++;
            counter = 0;
        }
    }
    //printf("\n");
}

void printBinary2(unsigned char value, int length, int height) {
    for (int i = 7; i >= 0; i--) {
        if(counterHeight==height){
            continue;
        }
        if((value >> i) & 1){
            printf("█ ");
        }else{
            printf("  ");
        }
        counter++;
        if(counter==length){
            printf("\n");
            counterHeight++;
            counter = 0;
        }
    }
}

void app_main(void)
{
    int letter = 'E';
    ESP_LOGI(TAG, "FreeMono9pt7bBitmaps: %d", sizeof(FreeMono9pt7bBitmaps));
    ESP_LOGI(TAG, "test: %d", FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].xAdvance);

    int widthOfLetter = FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].width;
    int heightOfLetter = FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].height;

    ESP_LOGI(TAG, "Char %c: \nBitmapOffset: %d \nWidth: %d \nHeight: %d \nxAdvence: %d \nxOffset: %d \nyOffset: %d \nyAdvance: %d \nFirstByte: %.4x", 
                                                                                                                        letter,
                                                                                                                        FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].bitmapOffset,
                                                                                                                        widthOfLetter,
                                                                                                                        heightOfLetter,
                                                                                                                        FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].xAdvance,
                                                                                                                        FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].xOffset,
                                                                                                                        FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].yOffset,
                                                                                                                        FreeMono9pt7b.yAdvance,
                                                                                                                        FreeMono9pt7bBitmaps[FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].bitmapOffset]);
    
    for(int i=0; i<(widthOfLetter * heightOfLetter / 8 +1);i++){
        printBinary2(FreeMono9pt7bBitmaps[FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].bitmapOffset + i],widthOfLetter, heightOfLetter);
    }

    for(int i=0; i<(widthOfLetter * heightOfLetter / 8 +1);i++){
        ESP_LOGI(TAG, "Bitmaps %d: %.4x", i, FreeMono9pt7bBitmaps[FreeMono9pt7bGlyphs[letter - FreeMono9pt7b.first].bitmapOffset + i]);
    }

}
