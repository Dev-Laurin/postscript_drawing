//main.cpp
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - 
								//only do this in one cpp file
#include <iostream>
#include "catch.hpp"

//Draw a Simple Square at (0,0)
TEST_CASE("On Page One", "Draw a Square"){
	//Make a Square
	Square s1(0,0); // Draw a Square in (x,y)
	REQUIRE( s1.printPostscript() == "/box {
									newpath
									moveto
									72 0 rlineto
									0 72 rlineto
									-72 0 rlineto
									closepath
									} def
									gsave
									0 0 box stroke
									grestore"); 
}

//Draw a Circle

//Draw a Polygon

//Draw a Rectangle

//Draw a Spacer

//Draw a Triangle