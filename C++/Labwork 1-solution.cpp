#include <bits/stdc++.h>
using namespace std;

class Point2D
{
	int x,y;
public:
	Point2D(){ x=0; y=0; }
	Point2D(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void print();
	~Point2D(){ x = 0; y = 0; }
};

Point2D::Point2D(int argx,int argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(int argx)
{
	x=argx;
}

void Point2D::setY(int argy)
{
	y = argy;
}

int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

void Point2D::print()
{
	cout << "(" << x << "," << y << ")";
}


class Triangle
{
        Point2D a,b,c;
    public:
        Triangle();
        Triangle(Point2D _a,Point2D _b,Point2D _c);
        Point2D get_a(){ return a;}
        Point2D get_b(){return b;}
        Point2D get_c(){return c;}
        void set_a(Point2D _a){a=Point2D(_a.getX(),_a.getY());}
        void set_b(Point2D _b){b=Point2D(_b.getX(),_b.getY());}
        void set_c(Point2D _c){c=Point2D(_c.getX(),_c.getY());}
        double Area();
        ~Triangle(){}
    protected:

};


Triangle::Triangle(){
    a=Point2D(0,0);
    b=Point2D(0,0);
    c=Point2D(0,0);
}

Triangle::Triangle(Point2D _a,Point2D _b,Point2D _c){
    a=Point2D(_a.getX(),_a.getY());
    b=Point2D(_b.getX(),_b.getY());
    c=Point2D(_c.getX(),_c.getY());
}

double Triangle::Area(){
    return abs(a.getX()*(b.getY())+b.getX()*(c.getY())+c.getX()*(a.getY())-b.getX()*(a.getY())-c.getX()*(b.getY())-a.getX()*(c.getY()))/2.0;
}

int dist(Point2D x,Point2D y){
    return pow((x.getX()-y.getX()),2)+pow((x.getY()-y.getY()),2);
}

int main(){
    Triangle abc(Point2D(2,3),Point2D(6,6), Point2D(0,0)), def(Point2D(9,9),Point2D(15,15), Point2D(3,15));
    if(abc.Area()==def.Area())
        cout<<"same area"<<"\n";
    else
        cout<<"not same area"<<"\n";
    if(dist(abc.get_a(),abc.get_b())/dist(def.get_a(),def.get_b())==dist(abc.get_b(),abc.get_c())/dist(def.get_b(),def.get_c()))
        cout<<"they are similar"<<"\n";
    else
        cout<<"they are not similar"<<"\n";
	return 0;
}
