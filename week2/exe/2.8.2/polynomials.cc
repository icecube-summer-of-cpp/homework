#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "polynomials.h"
using namespace std;


int input_order(void);
unique_ptr<double []> input_coeff(int order);
polynomials f(double c2, double c1, double c0);

struct not_valid_int_val{};
struct not_valid_coeff_val{};

int main(void){

	int order; // polynomial order
	unique_ptr<double []> coeff_value; // array for coefficient

	string output_name = "Result";
	ofstream result;


	// order = input_order(); 
	// Set polynomials order
	// polynomials poly = polynomials(order);
	// coeff_value = input_coeff(order);
	// poly.coeff_set(coeff_value.get());
	// poly.write(output_name.c_str());	

	
	polynomials poly2 = f(2, 3, 4);
	poly2.write(output_name);
	
}


// Checking the value is correct
int input_order(void){
	
	int order;
	try{
		cout << "Type order of polynmoial : ";
		cin >> order;
		if(cin.fail() || order < 0){
			throw not_valid_int_val{};
		} 
	} catch(not_valid_int_val &e){
		cout << "It is not valid input" << endl;
		cout << "Plase input int type value" << endl;
		exit(1);
	} catch(...){
		cout << "Error at " << __FUNCTION__ << endl;
		exit(1);
	}
	return order;
}

unique_ptr<double []> input_coeff(int order){
	unique_ptr<double []> coeff{new double[order + 1]};
	cout << "Type coefficent" << endl;

	try{
		for(int i = 0; i <= order; i++){
			cout << i << "th coefficient : ";
			cin >> coeff[i];
			if(cin.fail()){
				throw not_valid_coeff_val{};
			}
		}
	} catch(not_valid_coeff_val &e){
		cout << "It is not correct value" << endl;
		exit(1);
	}
	return coeff;
}

polynomials f(double c2, double c1, double c0){
	polynomials poly = polynomials(2);
	unique_ptr<double []> coeff_value{new double [3]};

	coeff_value[0] = c0;
	coeff_value[1] = c1;
	coeff_value[2] = c2;

	poly.coeff_set(coeff_value.get());
	return poly;
}