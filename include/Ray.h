//
// Created by ccampo on 17/01/18.
//

#ifndef FP3D_RAY_H
#define FP3D_RAY_H


#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray(Vector3& origin, Vector3& direction);
};


#endif //FP3D_RAY_H
