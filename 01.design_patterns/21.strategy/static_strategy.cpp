#include <iostream>
#include <vector>

class point_t
{
public:
	point_t() = default;
	point_t(int x, int y) : x_{x}, y_{y}
	{
	}

	auto setX(int x) -> void { x_ = x; }
	auto getX() const -> int { return x_; }
	auto setY(int y) -> void { y_ = y; }
	auto getY() const -> int { return y_; }

private:
	int x_;
	int y_;
};

class XMapper
{
public:
	auto map(point_t point)	-> int const { return point.getX(); }
};

class YMapper
{
public:
	auto map(point_t point)	-> int const { return point.getY(); }
};

template<typename M = XMapper>
class Client
{
public:
	template<typename U = std::vector<point_t>>
	Client(U &&points) : points_{std::forward<U>(points)}
	{
	}

	auto showCoordinate() -> void
	{
		M mapper;

		for(auto point : points_)
			std::cout << mapper.map(point) << std::endl;
	}

private:
	std::vector<point_t> points_;
};

int main(int argc, char *argv[])
{
	std::cout << "X coordinates:" << std::endl;
	Client xClient{{{1,2}, {2,3}, {3, 4}}};
	xClient.showCoordinate();
	std::cout << std::endl;

	std::cout << "X coordinates:" << std::endl;
	Client<YMapper> yClient{{{1,2}, {2,3}, {3, 4}}};
	yClient.showCoordinate();

	return EXIT_SUCCESS;
}
