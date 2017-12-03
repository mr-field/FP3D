//
// Created by ccampo on 28/11/17.
//

#ifndef TESTEXEC_LIGHT_H
#define TESTEXEC_LIGHT_H


#include "Vector3.h"
#include "../src/Object3D.h"

class Light : public Object3D {
public:
    Light(const Vector3 &position);
};


#endif //TESTEXEC_LIGHT_H
