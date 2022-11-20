#pragma once
#include <cmath>
/*
* Vector2D class 
************************************************************/
struct Vector2D {
public:
	float x = 0;
	float y = 0;

	Vector2D() : x{ 0.f }, y{ 0.f } {};

	Vector2D(float xVal, float yVal) : x{ xVal }, y{ yVal } {};

	static Vector2D One() {
		return Vector2D(1, 1);
	}
	static Vector2D Zero() {
		return Vector2D(0, 0);
	}

	static Vector2D Up() {
		return Vector2D(0, -1);
	}

	static Vector2D Right() {
		return Vector2D(1, 0);
	}

	static Vector2D Down() {
		return Vector2D(0, 1);
	}

	static Vector2D Left() {
		return Vector2D(-1, 0);
	}

	Vector2D& Add(const Vector2D& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		return *this;
	}

	Vector2D& Subtract(const Vector2D& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		return *this;
	}
	Vector2D& Multiply(const Vector2D& vector)
	{
		this->x *= vector.x;
		this->y *= vector.y;
		return *this;
	}

	Vector2D& MultiplyFloat(const float val) {
		this->x *= val;
		this->y *= val;
		return *this;
	}

	Vector2D& Divide(const Vector2D& vector)
	{
		this->x /= vector.x;
		this->y /= vector.y;
		return *this;
	}

	Vector2D& Normalize()
	{
		if (this->x == 0 || this->y == 0) { return *this; }

		float magnitude = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
		this->x /= magnitude;
		this->y /= magnitude;
		return *this;
	}

	static float Distance(Vector2D v1, Vector2D v2) {
		
		const float x = v2.x - v1.x;
		const float y = v2.y - v1.y;

		const float calc = ((x * x) + (y * y));

		return sqrt(calc);
	}


	/* Returns a new vector, doesn't affect the arguments */
	friend Vector2D operator+(Vector2D v1, const Vector2D& v2) { return v1.Add(v2); }
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2) { return v1.Subtract(v2); }
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2) { return v1.Multiply(v2); }
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2) { return v1.Divide(v2); }

	friend Vector2D operator*(Vector2D v1, const float value) { return v1.MultiplyFloat(value); }
	Vector2D& operator*=(const float value) { return this->MultiplyFloat(value); }

	Vector2D& operator+=(const Vector2D& v2) { return this->Add(v2); }
	Vector2D& operator-=(const Vector2D& v2) { return this->Subtract(v2); }
	Vector2D& operator*=(const Vector2D& v2) { return this->Multiply(v2); }
	Vector2D& operator/=(const Vector2D& v2) { return this->Divide(v2); }

	friend bool operator < (Vector2D v1, Vector2D v2) {
		return v1.x < v2.x&& v1.y < v2.y;
	}

	friend bool operator > (Vector2D v1, Vector2D v2) {
		return v1.x > v2.x&& v1.y > v2.y;
	}

	friend bool operator!= (Vector2D v1, Vector2D v2) {
		return v1.x != v2.x || v1.y != v2.y;
	}
	friend bool operator== (Vector2D v1, Vector2D v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}
};

struct Transform
{
protected:
	Vector2D m_Position = Vector2D::One();
	Vector2D m_Scale = Vector2D::One();

public:
	Transform() = default;

	Transform(float x, float y, float xS, float yS) {
		m_Position.x = x;
		m_Position.y = y;
		m_Scale.x = xS;
		m_Scale.y = yS;
	}

	Transform(Vector2D position, Vector2D scale) {
		m_Position = position;
		m_Scale = scale;
	}

	inline Vector2D& GetPosition() { return m_Position; }
	inline void SetPosition(const Vector2D& newPosition) { m_Position = newPosition; }
	inline void SetPosition(const float xPos, const float yPos) { m_Position.x = xPos; m_Position.y = yPos; }
	inline void AddPosition(const Vector2D& posAdd) { m_Position += posAdd; }
	inline void AddPosition(const float xPos, const float yPos) { m_Position += Vector2D(xPos, yPos); }


	inline Vector2D& GetScale() { return m_Scale; }
	inline void SetScale(const Vector2D& newScale) { m_Scale = newScale; }
	inline void SetScale(const float xScale, const float yScale) { m_Scale.x = xScale; m_Scale.y = yScale; }
};