//main.cpp
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - 
								//only do this in one cpp file
#include <iostream>
#include <fstream>
#include <cmath>
#include "catch.hpp"
#include "code.h"
using std::pow;
using std::ofstream;
using std::cout; 
using std::endl; 
int main() {
	Point p(1, 2);
	Point a;
	cout << a.getX() << a.getY() << endl;
	a = p;
	cout << a.getX() << a.getY() << endl;
	a += p;
	cout << a.getX() << a.getY() << endl;
	a = a / 2;
	cout << a.getX() << a.getY() << endl;
	ofstream out("output.ps");
	out << "200 400 translate\n";
	vector<Point> polyPoints;
	for (int i = 0; i < 10; i++) {
		Point temp(i * 10, pow(i, 2));
		polyPoints.push_back(temp);
	}
	free_polygon polyCurve(polyPoints, false);
	polyCurve.print(out);
	shared_ptr<shape> toP = make_shared<polygon>(3, 10);

	for (int i = 4; i<12; i++) {
		shared_ptr<polygon> cir = make_shared<polygon>(i, 20);
		toP = shared_ptr<shape>(new vertical({ toP,cir }));
	}
	toP = shared_ptr<shape>(new horizontal({ toP,toP,toP,toP,toP }));
	toP->print(out);
}
/*
ofstream out("output.ps"); //The postscipt file
int inch = 72; //Units in postscript


//File to output postscript
ofstream out("output.ps");

//Draw a Simple Square at (0,0)
TEST_CASE("Draw a Square", "On Page One"){
	SECTION("Draw the Default Square: 1 Inch"){
		//Make a Default Square
		ofstream test1;  
		square s1(inch); 
		s1.print(test1); 

		s1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ofstream answer; 
		answer << "newpath\n";  
			answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
			answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		//REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Square at (10,10)"){
		//REQUIRE("" == ""); 
	}
}

TEST_CASE("Draw a Rectangle", "On Page One"){
	SECTION("Draw the Default Rectangle: 2x4 Inches"){
		//Make a Default Square
		ofstream test1;  
		rectangle r1(inch*2, inch*4); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ofstream answer; 
		answer << "newpath\n";  
			answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
			answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
			answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 

		//REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Rectangle at (10,10)"){
		REQUIRE("" == ""); 
	}
}

TEST_CASE("Draw a Triangle", "On Page One"){
	SECTION("Draw the Default Triangle: 1 Inch"){
		//Make a Default Square
		ofstream test1;  
		triangle t1(inch*5); 
		t1.print(test1); 

		t1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		// ofstream answer; 
		// answer << "newpath\n";  
		// 	answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
		// 	answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
		// 	answer << "closepath\n" << "stroke" << endl; 

		// REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Triangle at (10,10)"){
	}
}

TEST_CASE("Draw a Circle", "On Page One"){
	SECTION("Draw the Default Circle: 1 Inch"){
		//Make a Default Square
		ofstream test1;  
		circle c1(inch*6); 
		c1.print(test1); 

		c1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		// ofstream answer; 
		// answer << "newpath\n";  
		// 	answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
		// 	answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
		// 	answer << "closepath\n" << "stroke" << endl; 

		// REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Triangle at (10,10)"){
	}
}

TEST_CASE("Draw a Polygon", "On Page One"){
	SECTION("Draw the Default Polygon: 1 Inch"){
		//Make a Default Square
		ofstream test1;  
		polygon p1(5, inch*6); 
		p1.print(test1); 

		p1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		// ofstream answer; 
		// answer << "newpath\n";  
		// 	answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
		// 	answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
		// 	answer << "closepath\n" << "stroke" << endl; 

		// REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Triangle at (10,10)"){
	}
}

TEST_CASE("Draw a Spacer", "On Page One"){
	SECTION("Draw the Default Spacer: 1 Inch"){
		//Make a Default Square
		ofstream test1;  
		spacer s1(inch*2, inch*2); 
		s1.print(test1); 

		s1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		// ofstream answer; 
		// answer << "newpath\n";  
		// 	answer << -0.5*inch << " " << -0.5*inch << " moveto\n"; 
		// 	answer << -0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << 0.5*inch << " lineto\n"; 
		// 	answer << 0.5*inch << " " << -0.5*inch << " lineto\n"; 
		// 	answer << "closepath\n" << "stroke" << endl; 

		// REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Triangle at (10,10)"){
	}
}
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
