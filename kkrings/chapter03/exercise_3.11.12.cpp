/**
 * Solutions to exercise 3.11.10, 3.11.11, and 3.11.12
 */
#include <cmath>
#include <iostream>

/**
 * @brief Trapezoid rule
 * Use the trapezoid rule to approximate the integral of the
 * function @p f.
 * @param f Function
 * @param a Lower integral limit
 * @param b Upper integral limit
 * @param n Split the interval into n steps.
 */
template<typename F, typename T>
T trapezoid(const F& f, const T& a, const T& b, unsigned int n = 1000)
{
    T h = (b - a) / n;
    T integral = h/2. * (f(a) + f(b));

    for (unsigned int j = 1; j < n; ++j)
    {
        integral += h * f(a + j*h);
    }

    return integral;
}

/**
 * @brief First derivative
 * Use the finite difference to approximate the first derivative of the
 * function @p f.
 */
template<typename F, typename T>
class derivative
{
    public:
        /**
         * Construct a first derivative functor that holds the evaluated
         * function @p f and the finite difference spacing @p h.
         * @param f Function object
         * @param h Finite difference spacing
         */
        derivative(const F& f, const T& h) : f(f), h(h) {}
        virtual ~derivative() = default;

        /**
         * Calculate the first derivative at the function value @p x.
         * @param x Function value
         * @return Derivative evaluated at @p x
         */
        T operator()(const T& x) const
        {
            return (f(x + h) - f(x)) / h;
        }

    private:
        const F& f;
        T h;
};

/**
 * @brief Higher derivatives
 * Recursively calculate the finite difference to approximate the n-th
 * derivative of a function @p f.
 * @tparam N Order of derivative
 */
template<typename F, typename T, unsigned int N>
class nth_derivative
{
    using previous = nth_derivative<F, T, N - 1>;

    public:
        /**
         * Construct a n-th derivative functor that holds the evaluated
         * function @p f and the finite difference spacing @p h.
         * @param f Function object
         * @param h Finite difference spacing
         */
        nth_derivative(const F& f, const T& h) : fs(f, h), h(h) {}

        /**
         * Calculate the n-th derivative at the function value @p x.
         * @param x Function value
         * @return Derivative evaluated at @p x
         */
        T operator()(const T& x) const
        {
            return (fs(x + h) - fs(x)) / h;
        }

    private:
        previous fs;
        T h;
};

template<typename F, typename T>
class nth_derivative<F, T, 1> : public derivative<F, T>
{
    using derivative<F, T>::derivative;
};

/**
 * Create higher order derivative of function @p f.
 * @param f Function object
 * @param h Finite difference spacing
 * @tparam N Order of derivative
 * @return Higher order derivative functor
 */
template<unsigned int N, typename F, typename T>
nth_derivative<F, T, N> make_nth_derivative(const F& f, const T& h)
{
    return nth_derivative<F, T, N>(f, h);
}

// functions that will be evaluated
double exp3f(double x)
{
    return std::exp(-3. * x);
}

struct exp3t
{
    double operator()(double x) const
    {
        return std::exp(-3. * x);
    }
};

double sin_cos(double x)
{
    if (x < 1.)
    {
        return std::sin(x);
    }
    else
    {
        return std::cos(x);
    }
}


int main()
{
    std::cout << "Integral of f(x) = exp(-3x) from 0 to 4:" << std::endl;

    std::cout << "Function as argument: "
              << trapezoid(exp3f, 0., 4.)
              << ", functor as argument: "
              << trapezoid(exp3t(), 0., 4.)
              << std::endl;

    std::cout << "Integral of f(x) = sin(x) if x < 1 and f = cos(x) if >= 1 "
                 "from 0 to 4: "
              << trapezoid(sin_cos, 0., 4.)
              << std::endl;

    // trapezoid(std::sin, 0., 2.);
    // Cannot infer template argument.

    std::cout << "Integral of first derivative f(x) = exp(-3x) from 0 to 4: "
              << trapezoid(make_nth_derivative<1>(exp3t(), 0.001), 0., 4.)
              << ", f(4) - f(0) = "
              << exp3f(4.) - exp3f(0.)
              << std::endl;

    auto f = [](double x){return 2.*std::cos(x) + x*x;};

    std::cout << "First derivative of f(x) = 2cos(x) + x**2 at x = 2: "
              << make_nth_derivative<1>(f, 0.001)(2.)
              << ", -2sin(2) + 2*2 = " << -2.*std::sin(2.) + 4.
              << std::endl;

    std::cout << "Second derivative of f(x) = 2cos(x) + x**2 at x = 2: "
              << make_nth_derivative<2>(f, 0.001)(2.)
              << ", -2cos(2) + 2 = " << -2.*std::cos(2.) + 2.
              << std::endl;
}
