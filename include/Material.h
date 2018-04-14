//
// Created by ccampo on 10/12/17.
//

#ifndef FP3D_MATERIAL_H
#define FP3D_MATERIAL_H


#include "Vector3.h"

typedef Vector3 ColorRGB;

class Material {
public:
    ColorRGB color;
    Material(const ColorRGB &color) : color(color) {}
};


#endif //FP3D_MATERIAL_H
