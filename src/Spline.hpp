
template<T>
class Spline
{
public:
    virtual T operator()(float p) const = 0;
    virtual T eval(float p) const = 0;
};


template<T>
class Hermite : public Spline
{
public:
    Hermite(){}
    Hermite(std::vector<T> &&v) : nodes(std::move(v)){}
    T operator()(float p) const ;
    T eval(float p) const ;

private:
    std::vector<T> nodes;
};
