//
// Created by ccampo on 28/11/17.
//

#include "Triangle.h"

Triangle::Triangle(Vertex &a, Vertex &b, Vertex &c) : a(a), b(b), c(c) {
    normal = (b.position - a.position).cross((c.position - b.position)).invert().normalise();

    ab = (b.position - a.position).cross(normal);
    float n = (c.position - a.position).dot(ab);
    ab = ab * (1 / n);

    ac = (c.position - a.position).cross(normal);
    float n2 = (b.position - a.position).dot(ac);
    ac = ac * (1 / n2);
}
