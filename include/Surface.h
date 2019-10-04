#ifdef SURFACE_H
#define SURFACE_H

#include "Utilities.h"
#include "Ray.h"

const int LAMBERTIAN = 0;
const int SPECULAR = 1;
const int LIGHTSOURCE = 2;

class Surface {
public:
	Surface(const ColorDb& color = ColorDb(0, 0, 0), const int& model = LAMBERTIAN);

	double GetReflectionCoefficient() const;
	const ColorDb& GetColor() const;
	const ColorDb& GetEmission() const;

	bool HasReflectionModel(const int& model) const {
		return model == reflectionModel;
	}
private:
	ColorDb color;
	int reflectionModel = LAMBERTIAN;
	double reflectionCoefficient = 0.8;
	ColorDb emission = ColorDb(0.0);

	ColorDb lambertianReflection() const;
	ColorDb specularReflection() const;
};
#endif // SURFACE_H
