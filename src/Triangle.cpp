//
// Created by ccampo on 28/11/17.
//

#include "Triangle.h"

Triangle::Triangle(Vertex &a, Vertex &b, Vertex &c) : a(a), b(b), c(c) {
    normal = (b.position - a.position).cross((c.position - b.position)).normalise();
}
