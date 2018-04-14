//
// Created by ccampo on 28/11/17.
//

#ifndef FP3D_LIGHT_H
#define FP3D_LIGHT_H


#include "Vector3.h"
#include "../src/Object3D.h"

typedef Vector3 ColorRGB;

class Light : public Object3D {
public:
    float intensity;
    ColorRGB color = ColorRGB(1, 1, 1);

    Light(const Vector3 &center) : Object3D(center) {}
};


#endif //FP3D_LIGHT_H
