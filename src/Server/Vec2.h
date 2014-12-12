#pragma once

struct Vec2 {
	static const Vec2 ZERO;
	static const Vec2 UNIT_X;
	static const Vec2 UNIT_Y;

	float x;
	float y;

	Vec2();
	Vec2(const Vec2& other);
	Vec2(const float x, const float y);

	Vec2& operator =(const Vec2& other);

	Vec2 operator -() const;

	Vec2 operator +(const Vec2& other) const;
	Vec2 operator -(const Vec2& other) const;
	Vec2 operator *(float other) const;
	Vec2 operator /(float other) const;

	Vec2& operator +=(const Vec2& other);
	Vec2& operator -=(const Vec2& other);
	Vec2& operator *=(float other);
	Vec2& operator /=(float other);

	float getLength() const;
	float getLengthSq() const;

	float getDistance(const Vec2& other) const;
	float getDistanceSq(const Vec2& other) const;

	float getAngle() const;
	float getAngle(const Vec2& other) const;

	float dot(const Vec2& other) const;

	void normalize();
	Vec2 getNormalized() const;

	void rotate(const Vec2& pivot, const float angle);
	Vec2 getRotated(const Vec2& pivot, const float angle) const;
};