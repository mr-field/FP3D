//
// Created by ccampo on 28/11/17.
//

#include "Light.h"

Light::Light(const Vector3 &position) : Object3D(position){
    transform = Matrix4::buildTranslationMatrix(position);
}
