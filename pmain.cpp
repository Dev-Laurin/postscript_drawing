#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "catch.hpp"
#include "code.h"
using std::pow;
using std::ofstream;
using std::cout; 
using std::endl; 
using std::ostringstream; 

double func(double ang){
	cout << std::sin(2*ang*3.1415/360) << endl;
	return 100*(std::sin(2*ang*3.1415/360));
}

int main(){
	ofstream out("output.ps");
	out << "200 400 translate\n";
	shared_ptr<shape> toP = make_shared<functionShape>(func,0,360,10);
	toP->print(out);
	/*
	ofstream out("output.ps");
	out << "200 400 translate\n";
	shared_ptr<shape> toP=make_shared<polygon>(3,10);

	for(int i=4;i<12;i++){
		shared_ptr<polygon> cir= make_shared<polygon>(i,20);
		toP=shared_ptr<shape>(new vertical({toP,cir}));
	}
	toP=shared_ptr<shape>(new horizontal({toP,toP,toP,toP,toP}));
	toP->print(out);*/
}
