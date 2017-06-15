#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <assert.h>
#include <initializer_list>
#include <algorithm>
#include <cstdarg>

// #define SEE_CALCULATION
using namespace std;
class polynomials{

	public:
		polynomials(unsigned degree) : deg{degree}, coeff{new double[deg + 1]}{
		}

		polynomials(const polynomials& p) : deg(p.deg), coeff{new double[deg + 1]}{

		}

		// polynomials(std::initializer_list<double> values) : deg(values.size()), coeff{new double[deg + 1]}{
		// 	std::copy(std::begin(values), std::end(values), std::begin(coeff));
		// }

		polynomials(std::initializer_list<double> values) : deg(values.size() - 1), coeff{new double[deg + 1]}{
			copy(begin(values), end(values), coeff);
		}

		polynomials& operator=(std::initializer_list<double> values){
			copy(begin(values), end(values), coeff);
		}


		polynomials& operator=(const polynomials& src){
			if(this == &src)
				return *this;
			
			assert(deg == src.deg);
			for(int i = 0; i <= deg; i++)
				coeff[i] = src.coeff[i];
			
			return *this;
		}


		~polynomials(){
			delete[] coeff;
		}

		void coeff_set(double * coeff_val){
			for(int i = 0; i <= deg; i++){
				coeff[i] = coeff_val[i];
			} 
		}

		double x_input(double x_val){
			double result = 0;
			for(int i = deg; i >= 0; i--){
				result += coeff[i] * pow(x_val, i);
#ifdef SEE_CALCULATION
				std::cout << coeff[i] << " x " << x_val << "^" << i;
				if(i != 0){
					std::cout << " + ";
				}
#endif
			} 
#ifdef SEE_CALCULATION
			std::cout << " = " << result << std::endl;
#endif		
			return result;
		}

		void write(string file_name){
			ofstream result;
			try{
				result.open(file_name);
			} catch(...){
				cout << "Error in opeing file" << endl;
				exit(1);
			}
				result << "x\tPolynomial" << endl;
			for(int i = 0; i < 10; i++){
				result << i << "\t" << x_input(i) << endl;
			}
			result.close();
		}

	private:
		unsigned deg; // degree
		double * coeff;
};