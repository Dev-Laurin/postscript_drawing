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

ofstream out("output.ps"); //The postscipt file
int inch = 72; //Units in postscript


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

		REQUIRE(test1 == answer); 
	}

	SECTION("Draw a Square at (10,10)"){
		REQUIRE("" == ""); 
	}
}

	//
//Parker's main.cpp code
    // ofstream out("output.ps");
    // out << "200 400 translate\n";
    // shared_ptr<shape> toP=make_shared<polygon>(3,10);

    // for(int i=4;i<12;i++){
    //     shared_ptr<polygon> cir= make_shared<polygon>(i,20);
    //     toP=shared_ptr<shape>(new vertical({toP,cir}));
    // }
    // toP=shared_ptr<shape>(new horizontal({toP,toP,toP,toP,toP}));
    // toP->print(out);


//Draw a Circle

//Draw a Polygon

//Draw a Rectangle

//Draw a Spacer

//Draw a Triangle