//main.cpp
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - 
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

/*
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
*/

//File to output postscript
ofstream out("testing.ps");
double inch = 72.0; //Units in postscript

//TEST THE BASIC SHAPES
TEST_CASE("Draw a Square", "On Page One"){

	SECTION("Draw a Square of length 0"){
		//Print shapes in middle of page, Global Coord
		out << "200 400 translate\n";

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

TEST_CASE("Draw a Spacer", "On Page One"){
	SECTION("Draw a Spacer of length 0"){
		//Make a Default
		ostringstream test1;  

		double height = 0; 
		double width = 0; 

		spacer r1(width, height); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		REQUIRE(test1.str() == ""); 
	}

	SECTION("Draw a Default Spacer: 2x4 inches"){
		//Make a Default
		ostringstream test1;  

		double height = inch*4; 
		double width = inch*2; 

		spacer r1(width, height); 
		r1.print(test1); 

		r1.print(out); //Put on Page 1 

		REQUIRE(test1.str() == ""); 
	}

	SECTION("Draw an arbitrarily large Spacer"){
	//Make a Default
	ostringstream test1;  

	double height = inch*10; 
	double width = inch*8; 

	spacer r1(width, height); 
	r1.print(test1); 

	r1.print(out); //Put on Page 1 

	REQUIRE(test1.str() == ""); 
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
			answer << -0.5*length << " " << round(-sin(60)*length-1) << " moveto\n";
			answer << "-" << 0 << " " << -round(2*(-sin(60)*length-1)) << " lineto\n"; 
			answer << 0.5*length << " " << round(-sin(60)*length-1) << " lineto\n"; 
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
	SECTION("Draw the Default Polygon: 5 sides"){
		//Make a Default
		ostringstream test1;  
		double length = inch*6; 
		polygon p1(5, length); 
		p1.print(test1); 

		p1.print(out); //Put on Page 1 

		//The postscript code that s1 should output
		ostringstream answer; 
		answer << "newpath\n";  
			answer << -216 << " " << 297 << " moveto\n"; 
			answer << -350 << " " << -114 << " lineto\n"; 
			answer << "-"<< 0 << " " << -367 << " lineto\n"; 
			answer << 349 << " " << -114 << " lineto\n";
			answer << 216 << " " << 297 << " lineto\n";  
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}




//TEST THE COMPOUND SHAPES
TEST_CASE("Draw Compound Shape Rotated", "On Page Two"){
	//Make a new page
	out << "showpage" << endl; 
	out << "200 400 translate\n";

	SECTION("Draw a Rotated Square: 45 Degrees"){
		ostringstream test1; 
		double length = inch; 
		int angle = 45; 

		shared_ptr<shape> sqPtr = make_shared<square>(length); 
		rotated r1(sqPtr, angle); 

		r1.print(out); //To postscript page
		r1.print(test1); //For testing only


		ostringstream answer; 
		answer << "gsave\n" << angle << " rotate\n"; 
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke\n" << "grestore" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw Compound Shape: Vertical", "On Page Two"){

	SECTION("Draw a Square-Circle-Square"){
		ostringstream test1; 
		double length = inch; 
		
		shared_ptr<shape> sqPtr = make_shared<square>(length); 
		shared_ptr<shape> cPtr = make_shared<circle>(length); 
		shared_ptr<shape> sqPtr2 = make_shared<square>(length); 

		vertical v({sqPtr,cPtr,sqPtr2}); 

		v.print(out); //To postscript page
		v.print(test1); //For testing only

		double boundBoxBuffer = 1.707125; 
		double boundBox = round(boundBoxBuffer * length); 

		ostringstream answer; 
		answer << "gsave\n"; 
		answer << 0 << " " << -boundBox << " translate\n"; 
		//Square
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		//Circle
			answer << 0 << " " << boundBox << " translate\n"; 
			answer << 0 << " " << 0 << " " << length << " "; 
			answer << 0 << " " << 360 << " arc stroke" << endl; 
		//Square
			answer << 0 << " " << boundBox << " translate\n"; 
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		 answer << "grestore" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Compound Shape: Horizontal", "On Page 2"){
	SECTION("Draw a Square-Circle-Square"){
		ostringstream test1; 
		double length = inch; 
		
		shared_ptr<shape> sqPtr = make_shared<square>(length); 
		shared_ptr<shape> cPtr = make_shared<circle>(length); 
		shared_ptr<shape> sqPtr2 = make_shared<square>(length); 

		horizontal h({sqPtr,cPtr,sqPtr2}); 

		h.print(out); //To postscript page
		h.print(test1); //For testing only

		double boundBoxBuffer = 1.707125; 
		double boundBox = round(boundBoxBuffer * length); 

		ostringstream answer; 
		answer << "gsave\n"; 
		answer << -boundBox << " " << 0 << " translate\n"; 
		//Square
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		//Circle
			answer << boundBox << " " << 0 << " translate\n"; 
			answer << 0 << " " << 0 << " " << length << " "; 
			answer << 0 << " " << 360 << " arc stroke" << endl; 
		//Square
			answer << boundBox << " " << 0 << " translate\n";  
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		 answer << "grestore" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Compound Shape: Layered", "On Page 3"){
	//New page
	out << "showpage" << endl; 
	out << "200 400 translate\n";

	SECTION("Draw a Layered object: Square-Circle-Square "){
		ostringstream test1; 
		double length = inch; 
		
		shared_ptr<shape> sqPtr = make_shared<square>(length); 
		shared_ptr<shape> cPtr = make_shared<circle>(length); 
		shared_ptr<shape> poPtr = make_shared<polygon>(5,length);

		layered l({sqPtr,cPtr,poPtr}); 

		l.print(out); //To postscript page
		l.print(test1); //For testing only

		ostringstream answer; 
		//Square
			answer << "newpath\n";  
			answer << -0.5*length << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke" << endl; 
		//Circle 
			answer << 0 << " " << 0 << " " << length << " "; 
			answer << 0 << " " << 360 << " arc stroke" << endl; 
		//Pentagon
			answer << "newpath\n";  
			answer << -36 << " " << 50 << " moveto\n"; 
			answer << -58 << " " << -19 << " lineto\n"; 
			answer << "-"<< 0 << " " << -61 << " lineto\n"; 
			answer << 58 << " " << -19 << " lineto\n";
			answer << 36 << " " << 50 << " lineto\n";  
			answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}

TEST_CASE("Draw a Compound Shape: Scaled", "On Page 3"){

	SECTION("Draw a Scaled Object: Square"){
		ostringstream test1; 
		double length = inch; 

		double xScaledFactor = 2; 
		double YScaledFactor = 3; 
		
		shared_ptr<shape> sqPtr = make_shared<square>(length); 

		scaled s(sqPtr, xScaledFactor, YScaledFactor); 

		s.print(out); //To postscript page
		s.print(test1); //For testing only

		ostringstream answer; 
		//Square
			answer << "gsave\n" << xScaledFactor << " "; 
			answer << YScaledFactor << " scale\n"; 
			answer << "newpath\n";  
			answer << (-0.5*length) << " " << 0.5*length << " moveto\n"; 
			answer << -0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << -0.5*length << " lineto\n"; 
			answer << 0.5*length << " " << 0.5*length << " lineto\n"; 
			answer << "closepath\n" << "stroke\n" << "grestore" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}
//TEST OUR OWN SHAPES

