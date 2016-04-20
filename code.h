//code.h
//Group - Parker, Lucas, Laurin, Dain
//Software Construction
//4-8-16

#ifndef CODE_H_INCLUDED
#define CODE_H_INCLUDED

#include <initializer_list>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <memory>
#include <functional>
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::sqrt;
using std::abs;
using std::pow;
using std::sin;
using std::cos;
using std::ofstream;
using std::string;
using std::cout;
using std::ostream;
using std::vector;
using std::initializer_list;
using std::min;
using std::max;


//Point class
//helper class for storing and doing operations on 2D points
//incomplete implementation, I am adding operations as I need them
class Point{
public:
	Point() {
		_x = 0;
		_y = 0;
	}
	Point(double x, double y) {
		_x = x;
		_y = y;	
	}
	void setX(int x) {
		_x = x;
	}
	void setY(int y) {
		_y = y;
	}
	double getX() {
		return _x;
	}
	double getY() {
		return _y;
	}
	Point operator+=(const Point& p) {
		this->_x = this->_x + p._x;
		this->_y = this->_y + p._y;
		return *this;
	}
	Point operator/(double d) {
		Point t;
		t._x = this->_x / d;
		t._y = this->_y / d;
		return t;
	}
	Point operator-(const Point& p) {
		Point t;
		t._x = this->_x - p._x;
		t._y = this->_y - p._y;
		return t;
	}
private:
	double _x;
	double _y;
};


//a pure virtual function that is a shape and has the ability to print to a o stream and knows its hitbox
class shape{
public:
    virtual ~shape(){}
    virtual void print(ostream& out) =0;
    double _hitX =10;
    double _hitY =10;

	//variables and bools for fill color, fill type, whether or not to fill
	//This is a quick and dirty way to get fill functionality into every shape,
	//and may be necessary due to the way things are designed. Would appreciate feedback if there is time.
	double _fRed = 1;
	double _fGreen = 1;
	double _fBlue = 1;
	double _fGray = 1;
	bool _fill = false;
	bool _fColor = false;
};


//section for shape groups and alignment

//a layed shape, takes a bunch of shapes by shared pointer and prints them on top of each other
//its hitbox will be the largest x hitbox and independently the largest y hitbox
class layered: public shape{
public:
    layered(initializer_list< shared_ptr<shape> > list){
        for(shared_ptr<shape> i:list){
            _shapes.push_back(i);
        }
        _hitX=0;
        _hitY=0;
        for(int i=0;i<_shapes.size();i++){
            _hitX=max(_hitX,_shapes[i]->_hitX);
            _hitY=max(_hitY,_shapes[i]->_hitY);
        }
    }
    void print(ostream& out) override{
        for(int i=0;i<_shapes.size();i++){
            _shapes[i]->print(out);
        }
    }
private:
    vector< shared_ptr<shape> > _shapes;
};


//holds one shape and will rotate the screen before printing it
//can rotate to any angle in degrees
class rotated: public shape{
public:
    rotated(shared_ptr<shape> shape,double ang){
        _shape=shape;
        _angle=ang;
        double pi=3.1415;
        //this is some basic trig to figure out the new hitbox based on the previous hitbox
        _hitX=sqrt(pow(_shape->_hitX*cos(_angle*pi/180.0),2.0)+pow(_shape->_hitY*sin(_angle*pi/180.0),2.0));
        _hitY=sqrt(pow(_shape->_hitY*cos(_angle*pi/180.0),2.0)+pow(_shape->_hitX*sin(_angle*pi/180.0),2.0));
        
    }
    void print(ostream& out) override{
        out << "gsave\n" << _angle << " rotate\n";
        _shape->print(out);
        out << "grestore\n";
    }
    ~rotated(){}
private:
    shared_ptr<shape> _shape;
    double _angle;
};

//takes a object and prints it as a larger shape scaled in x and y
class scaled: public shape{
public:
    scaled(shared_ptr<shape> toScale,double sX, double sY){
        _theShape=toScale;
        _sX=sX;
        _sY=sY;
        _hitX=_theShape->_hitX * _sX;
        _hitY=_theShape->_hitY * _sY;
    }
    void print(ostream& out) override{
        out << "gsave\n" << _sX << " " << _sY << " scale\n";
        _theShape->print(out);
        out << "grestore\n";
    }
private:
    shared_ptr<shape> _theShape;
    double _sX;
    double _sY;
};

//this creates a shape made out of many shapes stacked on top of each other
class vertical: public shape{
public:
    vertical(initializer_list< shared_ptr<shape> > list){
        for(shared_ptr<shape> i:list){
            _shapes.push_back(i);
        }
        _hitX=0;
        _hitY=0;
        for(int i=0;i<_shapes.size();i++){
            _hitX=max(_hitX,_shapes[i]->_hitX);
            _hitY+=_shapes[i]->_hitY;
        }
    }
    void print(ostream& out) override{
        out << "gsave\n0 " << -_hitY+_shapes[0]->_hitY << " translate\n"; //translate to the bottom of the object then up to where the center of the first shape shuld be
        _shapes[0]->print(out);//print out the first shape
        for(int i=1;i<_shapes.size();i++){
            //for the rest translate to the center of the shape and print
            out << "0 " << _shapes[i-1]->_hitY+_shapes[i]->_hitY << " translate\n";
            _shapes[i]->print(out);
        }
        out << "grestore\n";
    }
private:
    vector< shared_ptr<shape> > _shapes;
};

//basicaly the same as vertical but in the x direction
class horizontal: public shape{
public:
    horizontal(initializer_list< shared_ptr<shape> > list){
        for(shared_ptr<shape> i:list){
            _shapes.push_back(i);
        }
        _hitX=0;
        _hitY=0;
        for(int i=0;i<_shapes.size();i++){
            _hitY=max(_hitY,_shapes[i]->_hitY);
            _hitX+=_shapes[i]->_hitX;
        }
    }
    void print(ostream& out) override{
        out << "gsave\n" << -_hitX+_shapes[0]->_hitX << " 0 " << " translate\n";
        _shapes[0]->print(out);
        for(int i=1;i<_shapes.size();i++){
            out << _shapes[i-1]->_hitX+_shapes[i]->_hitX << " 0 "  << " translate\n";
            _shapes[i]->print(out);
        }
        out << "grestore\n";
    }
private:
    vector< shared_ptr<shape> > _shapes;
};


//class takes a shared_ptr<shape> object plus a line width variable
//    plus three color variables and appends gsave/n (n) setlinewidth/n (n) (n) (n) setrgbcolor/n ... grestore/n to the print
//OR takes a single color variable, which indicates grayscale and appends gsave/n (n) setlinewidth/n (n) setgray/n ... grestore/n to the print
//PRECONDITIONS: all passed variables must be positive.
//Note that setting the line width to greater than 1 can cause overlap in aligned objects.
//Additional note: This class does not update the hitbox (should be unnecessary)
class set_stroke : public shape {
public:
	set_stroke(shared_ptr<shape> s, double line_width, double red, double green, double blue) {
		_theShape = s;
		_line_width = line_width;
		_red = red;
		_green = green;
		_blue = blue;
		_color = true;
		_hitX = _theShape->_hitX;
		_hitY = _theShape->_hitY;
	}
	set_stroke(shared_ptr<shape> s, double line_width, double gray) {
		_theShape = s;
		_line_width = line_width;
		_gray = gray;
		_color = false;
		_hitX = _theShape->_hitX;
		_hitY = _theShape->_hitY;
	}
	void print(ostream& out) override {
		if (_color) {
			out << "gsave\n" << _line_width << " setlinewidth\n" << _red << " " << _green << " " << _blue << " setrgbcolor\n";
			_theShape->print(out);
			out << " grestore\n";
		}
		else {
			out << "gsave\n" << _line_width << " setlinewidth\n" << _gray << " setgray\n ";
			_theShape->print(out);
			out << "grestore\n";
		}
	}
private:
	shared_ptr<shape> _theShape;
	double _line_width;
	double _red;
	double _green;
	double _blue;
	double _gray;
	bool _color;
};

//------------------------------------
//PRECONDITIONS: all passed variables must be positive.
//this class does not add anything to the print. It simply modifies the fill variables in the shape virtual class.
//This is necessary due to the destructive nature of calling fill or stroke - the fill call must be made after the lines are
//drawn but before stroke is called. I can't think of an elegant method for inserting it here - it would require
//converting the ostream to a string, scanning for the stroke, and then inserting beforehand.
//It could also be done if, say, stroke and fill are created in an inherited class that we pass shapes into for printing.
//However, this method would break all of the tests. Bit of an impasse here.
class set_fill : public shape {
public:
	set_fill(shared_ptr<shape> s, double red, double green, double blue) {
		_theShape = s;
		_theShape->_fColor = true;
		_theShape->_fill = true;
		_theShape->_fRed = red;
		_theShape->_fGreen = green;
		_theShape->_fBlue = blue;
		_hitX = _theShape->_hitX;
		_hitY = _theShape->_hitY;
	}
	set_fill(shared_ptr<shape> s, double gray) {
		_theShape = s;
		_theShape->_fill = true;
		_theShape->_fGray = gray;
		_hitX = _theShape->_hitX;
		_hitY = _theShape->_hitY;
	}
	void print(ostream& out) override {
		_theShape->print(out);
	}
private:
	shared_ptr<shape> _theShape;
};

//these helper functions insert the gsave\n <color settings> fill\n grestore\n. It is called in every actual drawn shape object.
string fill_helper(double red, double green, double blue) {
	string h = "gsave\n " + std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue) + " setrgbcolor\nfill\ngrestore\n";
	return h;
}
string fill_helper(double gray) {
	string h = "gsave\n " + std::to_string(gray) + " setgray\nfill\ngrestore\n";
	return h;
}
//--------------------------------------- end of fill-related class and functions

//class takes an initializer list of shared_ptr to shape objects and appends showpage/n to the end.
//usage: No new transforms should be added to this shape once created. It is for final consolidation of a page of objects.
class page : public shape {
public:
	page(initializer_list<shared_ptr<shape>> list) {
		for (shared_ptr<shape> i : list) {
			_shapes.push_back(i);
		}
	}
	void print(ostream& out) override {
		for (int i = 0; i < _shapes.size(); i++) {
			_shapes[i]->print(out);
		}
		out << "showpage\n";
	}
private:
	vector<shared_ptr<shape>> _shapes;
};





//section for actual drawn shapes

//basic shape, a rectangle
class rectangle: public shape{
public:
    rectangle(double width,double height){
        _width=width;
        _hitX=_width/2;
        _height=height;
        _hitY=_height/2;
    }
    void print(ostream& out) override{
		out << "newpath\n"
			<< -.5*_width << " " << -.5*_height << " moveto\n"
			<< -.5*_width << " " << .5*_height << " lineto\n"
			<< .5*_width << " " << .5*_height << " lineto\n"
			<< .5*_width << " " << -.5*_height << " lineto\n"
			<< "closepath\n";
		if (_fill) {
			if (_fColor)
				out << fill_helper(_fRed, _fGreen, _fBlue);
			else
				out << fill_helper(_fGray);
		}
		out << "stroke\n";
    }
    ~rectangle(){}
private:
    double _width;
    double _height;
};

//a rectangle that doesn't print anything
class spacer: public shape{
public:
    spacer(double width,double height){
        _width=width;
        _hitX=_width/2;
        _height=height;
        _hitY=_height/2;
    }
    void print(ostream& out) override{
    }
    ~spacer(){}
private:
    double _width;
    double _height;
};

//a basic shape, circle
class circle: public shape{
public:
    circle(double radius){
        _radius=radius;
        _hitX=_radius;
        _hitY=_radius;
    }
    void print(ostream& out) override{
		out << "0 0 " << _radius << " 0 360 arc";
		if (_fill) {
			if (_fColor)
				out << fill_helper(_fRed, _fGreen, _fBlue);
			else
				out << fill_helper(_fGray);
		}
		out << " stroke\n";
    }
private:
    double _radius;
};

//a basic shape, a polygon of any number of sides
class polygon: public shape{
public:
    polygon(int sides,double length){
        _sides=sides;
        _angle=2.0*3.1415/_sides; //the angle formed by a side when viewed from the center
        _radius=length/(sin(_angle/2.0)*2.0); //how far from the center the vertecies are
        _hitX=_radius;
        _hitY=_radius;
        if((sides/2.0)*2.0==sides){ //how far the shape has to be rotated so the right side fases down
            _angleOffSet=3.1415/2.0+_angle/2.0;
        }else{
            _angleOffSet=3.1415/2.0;
        }
    }
    void print(ostream& out) override{
        out << "newpath\n";
        printPoint(out,0);
        out << " moveto\n";
            for(int i=1;i<_sides;i++){
                printPoint(out,i);
                out << " lineto\n";
            }
		out << "closepath\n";
		if (_fill) {
			if (_fColor)
				out << fill_helper(_fRed, _fGreen, _fBlue);
			else {
				out << fill_helper(_fGray);
			}
		}
		out << "stroke\n";
    }
private:
    void printPoint(ostream& out,int N){//knows where each vertex is
        double pointAngle=_angleOffSet+N*_angle;
        out << std::round(_radius*cos(pointAngle));
        out << " " << std::round(_radius*sin(pointAngle));
    }
    double _radius;
    double _angle;
    int _sides;
    double _angleOffSet;
};

//this object has a polygon wich is set to 4 sides
class square: public shape{
public:
    square(double length){
        _poly=shared_ptr<polygon>(new polygon(4,length));
        _hitX=_poly->_hitX;
        _hitY=_poly->_hitY;
    }
    void print(ostream& out) override{
        _poly->print(out);
    }
private:
    shared_ptr<shape> _poly;
};

//has a polygon with 3 sides
class triangle: public shape{
public:
    triangle(double length){
        _poly=shared_ptr<polygon>(new polygon(3,length));
        _hitX=_poly->_hitX;
        _hitY=_poly->_hitY;
    }
    void print(ostream& out) override{
        _poly->print(out);
    }
private:
    shared_ptr<shape> _poly;
};

//free_polygon class
//creates a closed or open shape from a vector of Point objects
class free_polygon : public shape {
public:
	//pass True in second argument for closed path, pass False for open path
	free_polygon(vector<Point> points, bool close) {
		Point centroid = get_centroid(points);
		for (int i = 0; i < points.size(); i++) {
			Point temp = points[i] - centroid;
			_normalized_points.push_back(temp);
		}
		_hitX = 0;
		_hitY = 0;
		for (int i = 0; i < _normalized_points.size(); i++) {
			_hitX = max(abs(_normalized_points[i].getX()), _hitX);
			_hitY = max(abs(_normalized_points[i].getY()), _hitY);
		}
		_close = close;

	}
	void print(ostream& out) override {
		out << "newpath\n";
		Point temp; // defaults to (0,0)
		printPoint(out, _normalized_points[0]);
		out << " moveto\n";
		for (int i = 1; i<_normalized_points.size(); i++) {
			printPoint(out, _normalized_points[i]);
			out << " lineto\n";
		}
		if(_close) out << "closepath\n";
		if (_fill) {
			if (_fColor)
				out << fill_helper(_fRed, _fGreen, _fBlue);
			else
				out << fill_helper(_fGray);
		}
		out << "stroke\n";
	}

private:
	void printPoint(ostream& out, Point p) {
		out << p.getX() << " " << p.getY();
	}
	Point get_centroid(vector<Point> points) {
		Point total;
		Point centroid;
		for (int i = 0; i < points.size(); i++) {
			total += points[i];
		}
		centroid = total / points.size();
		return centroid;
	}
	vector<Point> _normalized_points;
	bool _close;
};


class functionShape: public shape{
public:
	functionShape(function<double (double)> func,double minTheta,double maxTheta,double dTheta){
		_func=func;
		_min=minTheta;
		_max=maxTheta;
		_dt=dTheta;
		_hitX=0;
		_hitY=0;
		for(double ang=_min;ang<=_max;ang+=_dt){
			_hitX=max(_hitX,abs(_func(ang)*cos(toRad(ang))));
			_hitY=max(_hitY,abs(_func(ang)*sin(toRad(ang))));
		}
	}
	void print(ostream& out) override {
		out << "newpath\n";
		printPoint(out,_min);
		out << " moveto\n";
		for(double ang=_min+_dt;ang<=_max;ang+=_dt){
			printPoint(out,ang);
			out << " lineto\n";
		}
		out << "closepath\n";
		if (_fill) {
			if (_fColor)
				out << fill_helper(_fRed, _fGreen, _fBlue);
			else
				out << fill_helper(_fGray);
		}
		out << "stroke\n";
	}
private:
	void printPoint(ostream& out, double ang){
		out << _func(ang)*cos(toRad(ang)) << " " << _func(ang)*sin(toRad(ang));
	}
	double toDeg(double rad){
		return rad*360/3.1415;
	}
	double toRad(double deg){
		return deg*3.1415/360;
	}
	function<double (double)> _func;
	double _min;
	double _max;
	double _dt;
};

#endif  /* CODE_H_INCLUDED  */
