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
        out << "newpath\n"
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

class circle: public shape{
public:
    circle(double radious){
        _radious=radious;
        _hitX=_radious;
        _hitY=_radious;
    }
    void print(ostream& out) override{
        out << "0 0 " << _radious << " 0 360 arc stroke\n";
    }
private:
    double _radious;
};

class polygon: public shape{
public:
    polygon(int sides,double length){
        _sides=sides;
        _angle=2*3.1415/_sides;
        _radious=length/(sin(_angle/2)*2);
        _hitX=_radious;
        _hitY=_radious;
        if((sides/2)*2==sides){
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
    void printPoint(ostream& out,int N){
        double pointAngle=_angleOffSet+N*_angle;
        out << _radious*cos(pointAngle) << " " << _radious*sin(pointAngle);
    }
    double _radious;
    double _angle;
    int _sides;
    double _angleOffSet;
};

int main(){
    ofstream out("output.ps");
    out << "100 100 translate\n";
    shape* toP=new polygon(3,40);
    for(int i=4;i<12;i++){
        polygon* cir=new polygon(i,40);
        toP=new layered({toP,cir});
    }
    toP->print(out);
/*
    rectangle rec(1,1);
    rotated rotrec({&rec},45);
    scaled scaleSquare(&rotrec,100,100);
    scaled scaleSquare2(&rec,100,100);
    layered top{&scaleSquare,&scaleSquare2};
    top.print(out);*/
}
