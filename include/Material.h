//
// Created by ccampo on 10/12/17.
//

#ifndef TESTEXEC_MATERIAL_H
#define TESTEXEC_MATERIAL_H


#include "Vector3.h"

typedef Vector3 ColorRGB;

class Material {
public:
    ColorRGB color;
    Material(const ColorRGB &color) : color(color) {}
};


#endif //TESTEXEC_MATERIAL_H
