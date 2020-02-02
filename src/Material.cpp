#include "Material.h"

Direction Material::BRDF() {
	switch (type) {
		case LAMBERTIAN:
			return normalizationFactor;
		case PERFECT_REFLECTOR:
			return glm::vec3(1.0f);
		case LIGHT:
			return normalizationFactor;
	}
}