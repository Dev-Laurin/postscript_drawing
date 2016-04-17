//main.cpp
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - 
								//only do this in one cpp file
#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "code.h"
using std::ofstream;
using std::cout; 
using std::endl; 

//File to output postscript
ofstream out("output.ps");

//Draw a Simple Square at (0,0)
TEST_CASE("On Page One", "Draw a Square"){
	//Make a Square

	//Convert pixels to inches
	int inch = 72; 
	square s1(inch*4); 
	s1.print(out); 
	REQUIRE( "" == "");

	//Parker's testing code, for now, saved
    // rectangle rec(1,1);
    // rotated rotrec(&rec,45);
    // scaled scaleSquare(&rotrec,100,100);
    // scaled scaleSquare2(&rec,100,100);
    // layered top{&scaleSquare,&scaleSquare2};
    // top.print(out);

	//rectangle r(1,1); 
	REQUIRE( "" == ""); 
}

//Draw a Circle

//Draw a Polygon

//Draw a Rectangle

//Draw a Spacer

//Draw a Triangle