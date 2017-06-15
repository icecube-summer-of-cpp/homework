#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Polynomial
{
public:
	Polynomial(int _degree) : degree(_degree) {
		for (int i = 0; i < degree; ++i)
		{
			coeff[i] = 0.;
		}
	};
	Polynomial(int _degree, vector<double> _coeff)
	{
		assert(_degree == _coeff.size());
		degree = _degree;
		coeff = _coeff;
	};

	~Polynomial()
	{
		coeff.clear();
	};

	// Polynomial operator*(Polynomial poly, float f)
	// {

	// };

	int get_degree()
	{
		return degree;
	};

	double get_coeff(int i)
	{
		return coeff[i];
	};

private:
	int degree;
	vector<double> coeff;

};

ostream& operator<<(ostream& os, Polynomial& poly)
	{
		os << poly.get_coeff(0) << " * x^0";
		for (int i = 1; i < poly.get_degree() + 1; ++i)
		{
			os << " + " << poly.get_coeff(i) << " x^" << i;
		};
		return os;
	};

int main(int argc, char const *argv[])
{
	Polynomial p(2);
	cout << p << endl;

	return 0;
}