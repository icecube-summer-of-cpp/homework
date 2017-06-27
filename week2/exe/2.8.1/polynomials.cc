#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "polynomials.h"
using namespace std;


int input_order(void);
unique_ptr<double []> input_coeff(int order);

struct not_valid_int_val{};
struct not_valid_coeff_val{};

int main(void){

	int order; // polynomial order
	unique_ptr<double []> coeff_value; // array for coefficient

	string output_name = "Result";
	ofstream result;

	order = input_order(); 

	// Set polynomials order
	polynomials poly = polynomials(order);
	coeff_value = input_coeff(order);

	poly.coeff_set(coeff_value.get());

	// print from x = 0 to x = 10
	poly.write(output_name);	
	
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