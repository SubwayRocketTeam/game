#include "stdafx.h"
#include "Vec2.h"

const Vec2 Vec2::ZERO = Vec2();
const Vec2 Vec2::UNIT_X = Vec2(1, 0);
const Vec2 Vec2::UNIT_Y = Vec2(0, 1);


Vec2::Vec2() :x(0), y(0) {
}

Vec2::Vec2(const Vec2& other) :x(other.x), y(other.y) {
}

Vec2::Vec2(const float x, const float y) :x(x), y(y) {
}


Vec2& Vec2::operator =(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}


Vec2 Vec2::operator -() const {
	return Vec2(-x, -y);
}


Vec2 Vec2::operator +(const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator -(const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator *(float other) const {
	return Vec2(x * other, y * other);
}

Vec2 Vec2::operator /(float other) const {
	return Vec2(x / other, y / other);
}


Vec2& Vec2::operator +=(const Vec2& other) {
	return *this = *this + other;
}

Vec2& Vec2::operator -=(const Vec2& other) {
	return *this = *this - other;
}

Vec2& Vec2::operator *=(float other) {
	return *this = *this * other;
}

Vec2& Vec2::operator /=(float other) {
	return *this = *this / other;
}


float Vec2::getLength() const {
	return sqrtf(getLengthSq());
}

float Vec2::getLengthSq() const {
	return x*x + y*y;
}


float Vec2::getDistance(const Vec2& other) const {
	return sqrtf(getDistanceSq(other));
}

float Vec2::getDistanceSq(const Vec2& other) const {
	return (*this - other).getLengthSq();
}


float Vec2::getAngle() const {
	return atan2f(y, x);
}

float Vec2::getAngle(const Vec2& other) const {
	return (other - *this).getAngle();
}

float Vec2::dot(const Vec2& other) const {
	return x*other.x + y*other.y;
}


void Vec2::normalize() {
	*this = getNormalized();
}

Vec2 Vec2::getNormalized() const {
	return *this / getLength();
}


void Vec2::rotate(const Vec2& pivot, const float angle) {
	*this = getRotated(pivot, angle);
}

Vec2 Vec2::getRotated(const Vec2& pivot, const float angle) const {
	float sinAngle = sin(angle);
	float cosAngle = cos(angle);
	float tempX = x - pivot.x;
	float tempY = y - pivot.y;

	return Vec2(tempX * cosAngle - tempY * sinAngle + pivot.x,
		tempY * cosAngle + tempX * sinAngle + pivot.y);
}
