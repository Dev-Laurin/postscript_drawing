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
	//Parker's Example Output
	ofstream out("output.ps");
	out << "200 400 translate\n";
	shared_ptr<shape> top = make_shared<functionShape>(func,0,360,10);
	top->print(out);
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

	//Lucas' Example Output
	Point p(1, 2);
 	Point a;
	cout << a.getX() << a.getY() << endl;
 	a = p;
 	cout << a.getX() << a.getY() << endl;
 	a += p;
 	cout << a.getX() << a.getY() << endl;
 	a = a / 2;
	cout << a.getX() << a.getY() << endl;
	out << "showpage" << endl; 
 	out << "200 400 translate\n";
 	vector<Point> polyPoints;
 	for (int i = 0; i < 10; i++) {
 		Point temp(i * 10, pow(i, 2));
 		polyPoints.push_back(temp);
 	}
 	shared_ptr<shape> toP = make_shared<polygon>(3, 10);

 	for (int i = 4; i<12; i++) {
 		shared_ptr<polygon> cir = make_shared<polygon>(i, 20);
 		toP = shared_ptr<shape>(new vertical({ toP,cir }));
 	}
 	toP = shared_ptr<shape>(new horizontal({ toP,toP,toP,toP,toP }));
	toP = shared_ptr<shape>(new set_stroke(toP, 3, 0.75));
	toP = shared_ptr<shape>(new page({ toP }));
 	toP->print(out);
	shared_ptr<shape> polyPage = make_shared<free_polygon>(polyPoints, false);
	polyPage = shared_ptr<shape>(new page({ polyPage }));
	out << "200 400 translate\n";
	polyPage->print(out);
}
