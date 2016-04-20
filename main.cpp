//main.cpp
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - 
								//only do this in one cpp file
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

///*
 int main() {
 	ofstream out("output.ps");
 	out << "200 400 translate\n";
 	shared_ptr<shape> toP = make_shared<polygon>(3, 10);
	toP = shared_ptr<shape>(new set_fill(toP, 0));
	toP = shared_ptr<shape>(new set_stroke(toP, 1, 0));
 	for (int i = 4; i<12; i++) {
 		shared_ptr<shape> cir = make_shared<polygon>(i, 20);
		cir = shared_ptr<shape>(new set_fill(cir, 0.1*i));
		cir = shared_ptr<shape>(new set_stroke(cir, 0.1*i, 1 - 0.1*i));
 		toP = shared_ptr<shape>(new vertical({ toP,cir }));
 	}
 	toP = shared_ptr<shape>(new horizontal({ toP,toP,toP,toP,toP }));
	toP = shared_ptr<shape>(new page({ toP }));
 	toP->print(out);
	out << "200 400 translate\n";
	shared_ptr<shape> toP2 = make_shared<polygon>(3, 10);
	toP2 = shared_ptr<shape>(new set_fill(toP2, 0));
	toP2 = shared_ptr<shape>(new set_stroke(toP2, 0, 0));
	for (int i = 4; i<12; i++) {
		shared_ptr<shape> cir = make_shared<polygon>(i, 20);
		cir = shared_ptr<shape>(new set_fill(cir, 0.1*i,0,0));
		cir = shared_ptr<shape>(new set_stroke(cir, 0.3*i, 0, 0.1*i,0));
		toP2 = shared_ptr<shape>(new vertical({ toP2,cir }));
	}
	toP2 = shared_ptr<shape>(new horizontal({ toP2,toP2,toP2,toP2,toP2 }));
	toP2 = shared_ptr<shape>(new scaled(toP2, 0.5,0.5));
	toP2 = shared_ptr<shape>(new rotated(toP2, 30));
	toP2 = shared_ptr<shape>(new page({ toP2 }));
	toP2->print(out);
	out << "200 400 translate\n";
	vector<Point> polyPoints;
	Point a(0, 0);
	Point b(0, 4 * 72);
	Point c(2 * 72, 2 * 72);
	Point d(3 * 72, 4 * 72);
	polyPoints.push_back(a);
	polyPoints.push_back(b);
	polyPoints.push_back(c);
	polyPoints.push_back(d);
	shared_ptr<shape> polyPage = make_shared<free_polygon>(polyPoints, true);
	polyPage = shared_ptr<shape>(new set_fill(polyPage, 0, 0, 1));
	polyPage = shared_ptr<shape>(new page({ polyPage }));
	polyPage->print(out);
	out << "200 400 translate\n";
	auto rose = [](auto ang){
		double rad = cos(5*(ang*3.1415/360)) * 72;
		return rad;
	};
	shared_ptr<shape> funcShape = make_shared<functionShape>(rose, 0, 360, 0.1);
	funcShape = shared_ptr<shape>(new page({ funcShape }));
	funcShape->print(out);
 }
// */

/*
//File to output postscript
ofstream out("output.ps");
double inch = 72.0; //Units in postscript


TEST_CASE("Draw a Square", "On Page One"){

	SECTION("Draw a Square of length 0"){
		ostringstream test1; 
		double length = inch * 0; 
		square s1(length); 
		s1.print(test1); 

		s1.print(out); 

		//The postscript code that s1 should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		REQUIRE(test1.str() == answer.str()); 
	}

	SECTION("Draw the Default Square: 1 Inch"){
		//Make a Default Square
		ostringstream test1;   
		square s1(inch); 
		s1.print(test1); 

		s1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*inch << " " << 0.5*inch << " moveto\n"; 
			answer << -0.5*inch << " " << -0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		//Convert streams to strings for comparison
		REQUIRE(test1.str() == answer.str()); 
	}

		SECTION("Draw a Square of arbitrary size"){

		ostringstream test1;   
		double length = inch * 5; 
		square s1(length); 
		s1.print(test1); 

		s1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		//Convert streams to strings for comparison
		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Rectangle", "On Page One"){
	SECTION("Draw a Rectangle of length 0"){
		//Make a Default
		ostringstream test1;  

		double height = 0; 
		double width = 0; 

		rectangle r1(width, height); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*width << " " << -0.5*height << " moveto\n"; 
			answer << -0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << -0.5*height << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}

	SECTION("Draw the Default Rectangle: 2x4 Inches"){
		//Make a Default
		ostringstream test1;  

		double height = inch*4; 
		double width = inch*2; 

		rectangle r1(width, height); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*width << " " << -0.5*height << " moveto\n"; 
			answer << -0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << -0.5*height << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}

	SECTION("Draw an arbitrary large Rectangle"){
		//Make a Default
		ostringstream test1;  

		double height = inch*7; 
		double width = inch*5; 

		rectangle r1(width, height); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*width << " " << -0.5*height << " moveto\n"; 
			answer << -0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << 0.5*height << " lineto\n"; 
			answer << 0.5*width << " " << -0.5*height << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}


TEST_CASE("Draw a Triangle", "On Page One"){
	SECTION("Draw the Default Triangle: 1 Inch"){
		//Make a Default
		ostringstream test1;  

		double length = inch; 
		triangle t1(length); 
		t1.print(test1); 

		t1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*length << " " << round(sin(60)*length) << " moveto\n"; 
			answer << 0.5*length << " " << round(sin(60)*length) << " lineto\n"; 
			answer << 0.5*length << " " << round(sin(60)*length) << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Circle", "On Page One"){
		SECTION("Draw a Circle of radius 0"){
		//Make a Default 
		ostringstream test1; 
		double length = inch * 0;  
		circle c1(length); 
		c1.print(test1); 

		c1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer;   
		answer << 0 << " " << 0 << " " << length << " "; 
		answer << 0 << " " << 360 << " arc stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}

	SECTION("Draw the Default Circle: 1 Inch"){
		//Make a Default 
		ostringstream test1;  
		circle c1(inch); 
		c1.print(test1); 

		c1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer;   
		answer << 0 << " " << 0 << " " << inch << " "; 
		answer << 0 << " " << 360 << " arc stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}

	SECTION("Draw an arbitrarily large Circle"){
		//Make a Default 
		ostringstream test1;  
		double length = inch*5; 
		circle c1(length); 
		c1.print(test1); 

		c1.print(out); //Put on Page 1 

		//The postscript code that should output
		ostringstream answer;   
		answer << 0 << " " << 0 << " " << length << " "; 
		answer << 0 << " " << 360 << " arc stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Polygon", "On Page One"){
	SECTION("Draw the Default Polygon: 1 Inch"){
		//Make a Default
		ostringstream test1;  
		double length = inch*6; 
		polygon p1(5, length); 
		p1.print(test1); 

		p1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -0.5*length << " " << -0.5*inch << " moveto\n"; 
			answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

*/
//Parker's main.cpp code
/*
    ofstream out("output.ps");
    out << "200 400 translate\n";
    shared_ptr<shape> toP=make_shared<polygon>(3,10);

    for(int i=4;i<12;i++){
         shared_ptr<polygon> cir= make_shared<polygon>(i,20);
         toP=shared_ptr<shape>(new vertical({toP,cir}));
    }
    toP=shared_ptr<shape>(new horizontal({toP,toP,toP,toP,toP}));
    toP->print(out);
*/ 
