//
// Created by barte on 22.03.2025.
//

#include "../headers/TgaBuffer.h"

#include <bitset>
#include <cstdio>
#include <iostream>


TgaBuffer::TgaBuffer(int w, int h) : Buffer(w, h) {
}


int TgaBuffer::save() {
    unsigned short header[9] = {
        0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0100, 0x0100, 0x0820
    };

    FILE *f = fopen("sampleImage.tga", "wb+");
    if (f == nullptr) return -1;

    header[6] = w; //width
    header[7] = h; //height

    //for (int i = 0; i < w*h; i++) {
        //std::cout << std::bitset<32>(color[i]) << " i: " << i << std::endl;
    //}

    fwrite(header, 2, 9, f);
    fwrite(color, 4, w*h, f);

    fclose(f);

    return 0;
}
