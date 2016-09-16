#include <vector>
#include <cmath>

template<typename T>
class Spline
{
public:
	virtual T operator()(float p) const = 0;
	virtual T eval(float p) const = 0;
};


template<typename T>
class HermiteCardinal : public Spline<T>
{
public:
	HermiteCardinal(std::vector<T> &&v, float tension=0.1f, float weight=0.5f) : nodes(std::move(v)), tension(tension), weight(weight){}
	T operator()(float p) const {
		evaluate(p);
	}
	T eval(float p) const {
		evaluate(p);
	}

private:
	T evaluate(float p) const;
	float tension {0.1};
	float weight {0.5};
	std::vector<T> nodes;
};

template<typename T>
T HermiteCardinal<T>::evaluate(float p) const {
	double integral;
	double t = modf(p, &integral);
	double t3 = t*t*t;
	double t2 = t*t;
	int i = integral+1;

	auto &p0 = nodes[i-1];
	auto &p1 = nodes[i];
	auto &p2 = nodes[i+1];
	auto &p3 = nodes[i+2];

	auto m1 = float(1-tension)*(p2-p0)/weight;
	auto m2 = float(1-tension)*(p3-p1)/weight;

	return float(2*t3 - 3*t2 + 1)*p1 + float(t3 - 2*t2 + t)*m1 + float(-2*t3 + 3*t2)*p2 + float(t3 - t2)*m2;
}
