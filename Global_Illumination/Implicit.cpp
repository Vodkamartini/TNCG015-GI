#include "Implicit.h"

bool Implicit::rayIntersection(Ray& ray) {
	printf("\nERROR::Implicit in function rayIntersection: No override detected");
	return false;
}

// Analytic stable quadratic solver from: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
bool Implicit::stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1)
{
    // Return false if there are no real solutions
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;
    else if (discriminant == 0) x0 = x1 = -0.5 * b / a;
    else {
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discriminant)) :
            -0.5 * (b - sqrt(discriminant));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1) std::swap(x0, x1);

    return true;
}