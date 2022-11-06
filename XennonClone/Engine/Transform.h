#pragma once

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
	Vector2D& Divide(const Vector2D& vector)
	{
		this->x /= vector.x;
		this->y /= vector.y;
		return *this;
	}

	/* Returns a new vector, doesn't affect the arguments */
	friend Vector2D operator+(Vector2D v1, const Vector2D& v2) { return v1.Add(v2); }
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2) { return v1.Subtract(v2); }
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2) { return v1.Multiply(v2); }
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2) { return v1.Divide(v2); }

	Vector2D& operator*(float value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	Vector2D& operator+=(const Vector2D& v2) { return this->Add(v2); }
	Vector2D& operator-=(const Vector2D& v2) { return this->Subtract(v2); }
	Vector2D& operator*=(const Vector2D& v2) { return this->Multiply(v2); }
	Vector2D& operator/=(const Vector2D& v2) { return this->Divide(v2); }
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

	inline Vector2D& GetPosition() { return m_Position; }
	inline void SetPosition(const Vector2D& newPosition) { m_Position = newPosition; }
	inline void SetPosition(const float xPos, const float yPos) { m_Position.x = xPos; m_Position.y = yPos; }

	inline Vector2D& GetScale() { return m_Scale; }
	inline void SetScale(const Vector2D& newScale) { m_Scale = newScale; }
	inline void SetScale(const float xScale, const float yScale) { m_Scale.x = xScale; m_Scale.y = yScale; }
};