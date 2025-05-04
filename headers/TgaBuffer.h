//
// Created by barte on 22.03.2025.
//

#ifndef TGABUFFER_H
#define TGABUFFER_H

#include "../headers/Buffer.h"
#include "../headers/ITgaSavable.h"


class TgaBuffer : public Buffer, public ITgaSavable {
    public:
    TgaBuffer(int w, int h);

    int save() override;

};

#endif //TGABUFFER_H
