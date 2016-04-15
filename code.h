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
using std::sqrt;
using std::pow;
using std::sin;
using std::cos;
using std::ofstream;
using std::string;
using std::cout;
using std::ostream;
using std::vector;
using std::initializer_list;

class shape{
public:
    virtual ~shape(){}
    virtual void print(ostream& out) =0;
    double _hitX;
    double _hitY;
};

/*
class rotated: public shape{
public:
    rotated(std::initializer_list<shape*> list,double ang){
        for(shape* i:list){
            _shapes.push_back(i);
        }
        _angle=ang;
    }
    void print(ostream& out) override{
        out << "gsave\n" << _angle << " rotate\n";
        for(int i=0;i<_shapes.size();i++){
            _shapes[i]->print(out);
        }
        out << "grestore\n";
    }
    ~rotated(){}
private:
    vector<shape*> _shapes;
    double _angle;
};*/
class layered: public shape{
public:
    layered(std::initializer_list<shape*> list){
        for(shape* i:list){
            _shapes.push_back(i);
        }
    }
    void print(ostream& out) override{
        for(int i=0;i<_shapes.size();i++){
            _shapes[i]->print(out);
        }
    }
    ~layered(){}
private:
    vector<shape*> _shapes;
};


class rotated: public shape{
public:
    rotated(shape* shape,double ang){
        _shape=shape;
        _angle=ang;
        double pi=3.1415;
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
    shape* _shape;
    double _angle;
};

class scaled: public shape{
public:
    scaled(shape* toScale,double sX, double sY){
        _theShape=toScale;
        _sX=sX;
        _sY=sY;
    }
    void print(ostream& out) override{
        out << "gsave\n" << _sX << " " << _sY << " scale\n";
        _theShape->print(out);
        out << "grestore\n";
    }
private:
    shape* _theShape;
    double _sX;
    double _sY;
};



class rectangle: public shape{
public:
    rectangle(double width,double hight){
        _width=width;
        _hitX=_width/2;
        _hight=hight;
        _hitY=_hight/2;
    }
    void print(ostream& out) override{
        out << ".01 setlinewidth\nnewpath\n"
            << -.5*_width << " " << -.5*_hight << " moveto\n"
            << -.5*_width << " " << .5*_hight << " lineto\n"
            << .5*_width << " " << .5*_hight << " lineto\n"
            << .5*_width << " " << -.5*_hight << " lineto\n"
            << "closepath\nstroke\n";
    }
    ~rectangle(){}
private:
    double _width;
    double _hight;
};

class spacer: public shape{
    spacer(double width,double hight){
        _width=width;
        _hitX=_width/2;
        _hight=hight;
        _hitY=_hight/2;
    }
    void print(ostream& out) override{
    }
    ~spacer(){}
private:
    double _width;
    double _hight;
};

#endif /* CODE_H_INCLUDED */ 
