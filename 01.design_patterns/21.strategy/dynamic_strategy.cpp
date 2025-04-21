#include <iostream>
#include <memory>
#include <vector>

class point_t
{
public:
	point_t() = default;
	point_t(int x, int y) : x_{x}, y_{y}
	{
	}
	void setX(int x) { x_ = x; }
	int getX() const{ return x_; }

	void setY(int y) { y_ = y; }
	int getY() const { return y_; }
	
private:
	int x_{};
	int y_{};
};

class MappingStrategy
{
public:
	virtual int mapCoordinate(point_t point) const = 0;	
};

class XMappingStrategy : public MappingStrategy
{
public:
	int mapCoordinate(point_t point) const override { return point.getX(); }
};

class YMappingStrategy : public MappingStrategy
{
public:
	int mapCoordinate(point_t point) const override { return point.getY(); }
};


class Client
{
public:
	Client(std::unique_ptr<MappingStrategy> mapper, std::vector<point_t> points) :
		mapper_{std::move(mapper)}, points_{points}
	{
	}
	void showCoordinate() const
	{
		for(auto point : points_)
			std::cout << mapper_->mapCoordinate(point) << std::endl;
	}

private:
	std::unique_ptr<MappingStrategy> mapper_;
	std::vector<point_t> points_;
};

int main(int argc, char *argv[])
{
	auto points{std::vector<point_t>{{0,0}, {0,1}, {0,2}, {5, 1}, {6,2}}};

	std::cout << "X coordinates :" << std::endl;
	auto xMapper{std::make_unique<XMappingStrategy>()};
	Client xClient{std::move(xMapper), points};
	xClient.showCoordinate();
	std::cout << std::endl;

	std::cout << "Y coordinates :" << std::endl;
	auto yMapper{std::make_unique<YMappingStrategy>()};
	Client yClient{std::move(yMapper), points};
	yClient.showCoordinate();

	return EXIT_SUCCESS;
}
