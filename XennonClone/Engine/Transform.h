#pragma once


struct Vector2D {
public:
	float x;
	float y;

	Vector2D() {
		x = 0.f;
		y = 0.f;
	}

	Vector2D(float xVal, float yVal) {
		x = xVal;
		y = yVal;
	}

	static Vector2D One() {
		return Vector2D(1, 1);
	}
};

struct Transform
{
protected:
	Vector2D m_Position = Vector2D::One();
	Vector2D m_Scale = Vector2D::One();

public:
	Transform(float x, float y, float xS, float yS);
	Transform();

	inline Vector2D GetPosition() { return m_Position; }
	inline void SetPosition(Vector2D newPosition) { m_Position = newPosition; }
	inline void SetPosition(float xPos, float yPos) { m_Position = Vector2D(xPos, yPos); }

	inline Vector2D GetScale() { return m_Scale; }
	inline void SetScale(Vector2D newScale) { m_Scale = newScale; }
	inline void SetScale(float xScale, float yScale) { m_Scale = Vector2D(xScale, yScale); }
};

