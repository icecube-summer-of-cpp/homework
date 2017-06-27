#include <iostream>
#include <math.h>
#include <memory>
#include <string>
// #include <stream>
// #define SEE_CALCULATION
using namespace std;
class polynomials{

	public:
		polynomials(unsigned degree) : deg{degree}, coeff{new double[deg + 1]}{
			std::cout << deg << std::endl;
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
		}

	private:
		unsigned deg; // degree
		double * coeff;
};