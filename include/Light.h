//
// Created by ccampo on 28/11/17.
//

#ifndef TESTEXEC_LIGHT_H
#define TESTEXEC_LIGHT_H


#include "Vector3.h"
#include "../src/Object3D.h"

typedef Vector3 ColorRGB;

class Light : public Object3D {
public:
    Light(const Vector3 &position);
    float intensity;
    ColorRGB color = ColorRGB(1, 1, 1);
};


#endif //TESTEXEC_LIGHT_H
