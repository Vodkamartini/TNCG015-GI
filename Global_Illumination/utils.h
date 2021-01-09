#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <glm/glm.hpp>


enum material {
	LAMBERTIAN,
	PERFECT_REFLECTOR,
	LIGHT_SOURCE
};

typedef glm::vec4 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl;

// Define constants
const float EPSILON = 0.000000001f;
const float M_PI = 3.14159265358979323846f;
const std::size_t MAX_DEPTH = 5;
const std::size_t SHADOW_RAY_COUNT = 2;
const std::size_t DEFAULT_WIDTH = 800;
const std::size_t DEFAULT_HEIGHT = 800;
const ColorDbl RED(255.0, 0, 0);
const ColorDbl GREEN(0, 255.0, 0);
const ColorDbl BLUE(0, 0, 255.0);

// Random stuff
static std::default_random_engine GENERATOR;
static std::uniform_real_distribution<double> DISTR(0.0, 1.0);

double uniformRand();
double randMinMax(const double& min, const double& man);

inline float deg2rad(const float& deg) {
	return deg * M_PI / 180;
}

template <typename T> class Array2D {
public:
	Array2D() : _width(DEFAULT_WIDTH), _height(DEFAULT_HEIGHT) {
		_data.resize(_width * _height);
	}

	Array2D(const std::size_t width, const std::size_t height) : _width(width), _height(height) {
		_data.resize(_width * _height);
	};

	T* get(std::size_t x, std::size_t y) { return &(_data[getPosition(x, y)]); };
	void set(T value, std::size_t x, std::size_t y) { _data[getPosition(x, y)] = value; };
	const std::size_t size() const { return _width * _height; };
	const std::size_t width() const { return _width; };
	const std::size_t height() const { return _height; };

private:
	std::size_t getPosition(std::size_t x, std::size_t y) { return x + (_width * y); };

	std::size_t _width, _height;
	std::vector<T> _data;
};