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
	Point operator/(const double& d) {
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
};


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
        _hitX=sqrt(pow(_shape->_hitX*cos(_angle*pi/180),2)+pow(_shape->_hitY*sin(_angle*pi/180),2));
        _hitY=sqrt(pow(_shape->_hitY*cos(_angle*pi/180),2)+pow(_shape->_hitX*sin(_angle*pi/180),2));
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
            << "closepath\nstroke\n";
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
        out << "0 0 " << _radius << " 0 360 arc stroke\n";
    }
private:
    double _radius;
};

//a basic shape, a polygon of any number of sides
class polygon: public shape{
public:
    polygon(int sides,double length){
        _sides=sides;
        _angle=2*3.1415/_sides; //the angle formed by a side when viewed from the center
        _radius=length/(sin(_angle/2)*2); //how far from the center the vertecies are
        _hitX=_radius;
        _hitY=_radius;
        if((sides/2)*2==sides){ //how far the shape has to be rotated so the right side fases down
            _angleOffSet=3.1415/2+_angle/2;
        }else{
            _angleOffSet=3.1415/2;
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
        out << "closepath\nstroke\n";
    }
private:
    void printPoint(ostream& out,int N){//knows where each vertex is
        double pointAngle=_angleOffSet+N*_angle;
        out << _radius*cos(pointAngle) << " " << _radius*sin(pointAngle);
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
		if(_close) out << "closepath\nstroke\n";
		else out << "stroke\n";
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

#endif  CODE_H_INCLUDED  

//To Test put in file main.cpp (catch testing framework)->

// int main(){
//     ofstream out("output.ps");
//     out << "200 400 translate\n";
//     shared_ptr<shape> toP=make_shared<polygon>(3,10);

//     for(int i=4;i<12;i++){
//         shared_ptr<polygon> cir= make_shared<polygon>(i,20);
//         toP=shared_ptr<shape>(new vertical({toP,cir}));
//     }
//     toP=shared_ptr<shape>(new horizontal({toP,toP,toP,toP,toP}));
//     toP->print(out);
// /*
//     rectangle rec(1,1);
//     rotated rotrec({&rec},45);
//     scaled scaleSquare(&rotrec,100,100);
//     scaled scaleSquare2(&rec,100,100);
//     layered top{&scaleSquare,&scaleSquare2};
//     top.print(out);*/
// }
// <-
