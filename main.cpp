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
 	ofstream out("output.ps");
 	out << "200 400 translate\n";
 	std::shared_ptr<shape> toP = std::make_shared<polygon>(3, 10);
	toP = std::shared_ptr<shape>(new set_fill(toP, 0));
	toP = std::shared_ptr<shape>(new set_stroke(toP, 1, 0));
 	for (int i = 4; i<12; i++) {
 		std::shared_ptr<shape> cir = std::make_shared<polygon>(i, 20);
		cir = std::shared_ptr<shape>(new set_fill(cir, 0.1*i));
		cir = std::shared_ptr<shape>(new set_stroke(cir, 0.1*i, 1 - 0.1*i));
 		toP = std::shared_ptr<shape>(new vertical({ toP,cir }));
 	}
 	toP = std::shared_ptr<shape>(new horizontal({ toP,toP,toP,toP,toP }));
	toP = std::shared_ptr<shape>(new page({ toP }));
 	toP->print(out);
	out << "200 400 translate\n";
	std::shared_ptr<shape> toP2 = std::make_shared<polygon>(3, 10);
	toP2 = std::shared_ptr<shape>(new set_fill(toP2, 0));
	toP2 = std::shared_ptr<shape>(new set_stroke(toP2, 0, 0));
	for (int i = 4; i<12; i++) {
		std::shared_ptr<shape> cir = std::make_shared<polygon>(i, 20);
		cir = std::shared_ptr<shape>(new set_fill(cir, 0.1*i,0,0));
		cir = std::shared_ptr<shape>(new set_stroke(cir, 0.3*i, 0, 0.1*i,0));
		toP2 = std::shared_ptr<shape>(new vertical({ toP2,cir }));
	}
	toP2 = std::shared_ptr<shape>(new horizontal({ toP2,toP2,toP2,toP2,toP2 }));
	toP2 = std::shared_ptr<shape>(new scaled(toP2, 0.5,0.5));
	toP2 = std::shared_ptr<shape>(new rotated(toP2, 30));
	toP2 = std::shared_ptr<shape>(new page({ toP2 }));
	toP2->print(out);
	out << "200 400 translate\n";
	std::vector<Point> polyPoints;
	Point a(0, 0);
	Point b(0, 4 * 72);
	Point c(2 * 72, 2 * 72);
	Point d(3 * 72, 4 * 72);
	polyPoints.push_back(a);
	polyPoints.push_back(b);
	polyPoints.push_back(c);
	polyPoints.push_back(d);
	std::shared_ptr<shape> polyPage = std::make_shared<free_polygon>(polyPoints, true);
	polyPage = std::shared_ptr<shape>(new set_fill(polyPage, 0, 0, 1));
	polyPage = std::shared_ptr<shape>(new page({ polyPage }));
	polyPage->print(out);
	out << "200 400 translate\n";
	auto rose = [](auto ang){
		double rad = cos(5*(ang*3.1415/360)) * 72;
		return rad;
	};
	std::shared_ptr<shape> funcShape = std::make_shared<functionShape>(rose, 0, 360, 0.1);
	funcShape = std::shared_ptr<shape>(new page({ funcShape }));
	funcShape->print(out);
 }
 */

///*
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

		std::shared_ptr<shape> sqPtr = std::make_shared<square>(length); 
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
		
		std::shared_ptr<shape> sqPtr = std::make_shared<square>(length); 
		std::shared_ptr<shape> cPtr = std::make_shared<circle>(length); 
		std::shared_ptr<shape> sqPtr2 = std::make_shared<square>(length); 

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
		
		std::shared_ptr<shape> sqPtr = std::make_shared<square>(length); 
		std::shared_ptr<shape> cPtr = std::make_shared<circle>(length); 
		std::shared_ptr<shape> sqPtr2 = std::make_shared<square>(length); 

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
		
		std::shared_ptr<shape> sqPtr = std::make_shared<square>(length); 
		std::shared_ptr<shape> cPtr = std::make_shared<circle>(length); 
		std::shared_ptr<shape> poPtr = std::make_shared<polygon>(5,length);

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
		
		std::shared_ptr<shape> sqPtr = std::make_shared<square>(length); 

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
TEST_CASE("Draw a Free Polygon (non-symmetric)", "On Page 4"){
	//New page
	out << "showpage" << endl; 
	out << "200 400 translate\n";
	SECTION("Draw a Free Polygon, 4 different non-symmetric points"){
		ostringstream test1; 
		std::vector <Point> pts; 

		Point p1; //(0,0)
		Point p2(1,1); 
		Point p3(3,-5); 
		Point p4(1,-2); 
		
		pts.push_back(p1); 
		pts.push_back(p2); 
		pts.push_back(p3); 
		pts.push_back(p4); 

		free_polygon fp(pts,true); 

		fp.print(out); //To postscript page
		fp.print(test1); //For testing only

		ostringstream answer; 
		answer << "newpath\n";  
		answer << -1.25 << " " << 1.5 << " moveto\n"; 
		answer << -0.25 << " " << 2.5 << " lineto\n"; 
		answer << 1.75 << " " << -3.5 << " lineto\n"; 
		answer << -0.25 << " " << -0.5 << " lineto\n"; 
		answer << "closepath\n" << "stroke" << endl; 

		REQUIRE(test1.str() == answer.str()); 
	}
}
//*/