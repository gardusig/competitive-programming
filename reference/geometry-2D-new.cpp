#include <bits/stdc++.h>

namespace geometry2D
{
template <typename T>
class PointVector
{
public:
	T x, y;

	PointVector(const T &x, const T &y);

	const PointVector<T> operator+(const PointVector<T> &other) const;
	const PointVector<T> operator-(const PointVector<T> &other) const;
	const PointVector<T> operator*(const T &k) const;
	const PointVector<T> operator/(const T &k) const;

	const bool operator<(const PointVector<T> &other) const;
	const bool operator==(const PointVector<T> &other) const;
};

template <typename T>
class LineRaySegment
{
public:
	T a, b, c;
	PointVector<T> start, finish, direction;

	LineRaySegment(const T &a, const T &b, const T &c);
	LineRaySegment(const PointVector<T> &start, const PointVector<T> &finish);
};

template <typename T>
class Circle
{
public:
	PointVector<T> center;
	T r;

	Circle() {}
	Circle(const PointVector<T> &center, const T &r);
};

template <typename T>
inline PointVector<T>::PointVector(const T &x, const T &y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator+(const PointVector<T> &other) const
{
	return PointVector<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator-(const PointVector<T> &other) const
{
	return PointVector<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator*(const T &k) const
{
	return PointVector<T>(this->x * k, this->y * k);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator/(const T &k) const
{
	return PointVector<T>(this->x / k, this->y / k);
}

template <typename T>
inline const bool PointVector<T>::operator<(const PointVector<T> &other) const
{
	if (this->x == other.x)
	{
		return this->y < other.y;
	}
	return this->x < other.x;
}

template <typename T>
inline const bool PointVector<T>::operator==(const PointVector<T> &other) const
{
	return this->x == other.x and this->y == other.y;
}

} // namespace geometry2D

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	geometry2D::PointVector<int> A(0, 0);
	geometry2D::PointVector<int> B(1, 1);

	const auto C = A + B;

	std::cout << C.x << ' ' << C.y << std::endl;

	return 0;
}