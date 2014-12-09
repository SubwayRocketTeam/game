#pragma once

struct Vec2 {
	static Vec2 ZERO;
	static Vec2 UNIT_X;
	static Vec2 UNIT_Y;

	float x;
	float y;

	Vec2();
	Vec2(const Vec2& other);
	Vec2(const float x, const float y);

	inline Vec2& operator =(const Vec2& other);

	inline Vec2&& operator +(const Vec2& other) const;
	inline Vec2&& operator -(const Vec2& other) const;
	inline Vec2&& operator *(float other) const;
	inline Vec2&& operator /(float other) const;

	inline Vec2& operator +=(const Vec2& other);
	inline Vec2& operator -=(const Vec2& other);
	inline Vec2& operator *=(float other);
	inline Vec2& operator /=(float other);

	inline float getLength() const;
	inline float getLengthSq() const;

	inline float getDistance(const Vec2& other) const;
	inline float getDistanceSq(const Vec2& other) const;

	inline float getAngle() const;

	inline float dot(const Vec2& other) const;

	inline void normalize();
	inline Vec2&& getNormalized() const;

	void rotate(const Vec2& pivot, const float angle);
	Vec2&& getRotated(const Vec2& pivot, const float angle) const;
};