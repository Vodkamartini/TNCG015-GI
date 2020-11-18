#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

const float EPSILON = 0.000000001f;
const float M_PI = 3.14159265358979323846f;
const size_t DEFAULT_WIDTH = 800;
const size_t DEFAULT_HEIGHT = 800;

enum material {
	LAMBERTIAN,
	PERFECT_REFLECTOR,
	LIGHT_SOURCE
};

typedef glm::vec4 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl;

inline float deg2rad(const float& deg) {
	return deg * M_PI / 180;
}

template <typename T> class Array2D {
public:
	Array2D() : _width(DEFAULT_WIDTH), _height(DEFAULT_HEIGHT) {
		_data.resize(_width * _height);
	}

	Array2D(const size_t width, const size_t height) : _width(width), _height(height) {
		_data.resize(_width * _height);
	};

	T* get(size_t x, size_t y) { return &(_data[getPosition(x, y)]); };
	void set(T value, size_t x, size_t y) { _data[getPosition(x, y)] = value; };
	const size_t size() const { return _width * _height; };
	const size_t width() const { return _width; };
	const size_t height() const { return _height; };

private:
	size_t getPosition(size_t x, size_t y) { return x + (_width * y); };

	size_t _width, _height;
	std::vector<T> _data;
};