#include <iostream>
#include <cstdio>
#include <cmath>
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

class Circle
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(Point2D c,double r);
	Point2D getCenter(){ return center; }
	double getRadius(){ return radius; }
	void set_center(Point2D _center){ center=_center; }
	void set_centerX(int _centerX){ center.setX(_centerX); }
	void set_centerY(int _centerY){ center.setY(_centerY); }
	void set_radius(double _radius){ radius=_radius; }
	double area(){ return 3.1416*radius*radius; }
	void print();
	int intersect(Circle rhs);
	int contains(Circle rhs);
	int contains(Point2D p);
	double perimeter(){ return 2*3.1416*radius; }
	~Circle();
};

Circle::Circle(){
	center.setX(0);
	center.setY(0);
	radius=0;
}

Circle::Circle(Point2D c,double r){
	center=c;
	radius=r;
}

Circle::~Circle(){
	center.setX(0);
	center.setY(0);
	radius=0;
}

int Circle::intersect(Circle rhs){
	double disCen=sqrt((pow((center.getX()-rhs.getCenter().getX()),2)+pow((center.getY()-rhs.getCenter().getY()),2)));
	if (disCen>fabs(radius-rhs.getRadius()) && disCen<(radius+rhs.getRadius())){
		return 1;
	}
	return 0;
}

int Circle::contains(Circle rhs){
	double disCen=sqrt((pow((center.getX()-rhs.getCenter().getX()),2)+pow((center.getY()-rhs.getCenter().getY()),2)));
	if (disCen<(radius-rhs.getRadius())){
		return 1;
	}
	return 0;
}

int Circle::contains(Point2D p){
	// (x-h)^2+(y-k)^2<r^2
	if ((pow((p.getX()-center.getX()),2)+pow((p.getY()-center.getY()),2))<pow(radius,2)){
		return 1;
	}
	return 0;
}

void Circle::print(){
	cout<<"Center: ";
	center.print();
	cout<<"Radius: "<<radius;
}

class Rectangle
{
	Point2D tR,bL;//tR for topRight and bL for bottomLeft
public:
	Rectangle();
	Rectangle(Point2D tr,Point2D bl){ tR=tr; bL=bl; }
	Point2D get_tR(){ return tR; }
	Point2D get_bL(){ return bL; }
	void set_tR(Point2D _tR){ tR=_tR; }
	void set_bL(Point2D _bL){ bL=_bL; }
	void set_tRX(int _tRX){ tR.setX(_tRX); }
	void set_tRY(int _tRY){ tR.setY(_tRY); }
	void set_bLX(int _bLX){ bL.setX(_bLX); }
	void set_bLY(int _bLY){ bL.setY(_bLY); }
	double area(){ return (tR.getX()-bL.getX())*(tR.getY()-bL.getY()); }
	double perimeter(){ return 2*(tR.getX()-bL.getX())+2*(tR.getY()-bL.getY()); }
	int contains(Rectangle rhs);
	int intersect(Rectangle rhs);
	int inside(Circle c);
	~Rectangle();
};

Rectangle::Rectangle(){
	tR.setX(0);
	tR.setY(0);
	bL.setX(0);
	bL.setY(0);
}

Rectangle::~Rectangle(){
	tR.setX(0);
	tR.setY(0);
	bL.setX(0);
	bL.setY(0);
}

int Rectangle::contains(Rectangle rhs){
	int trx=tR.getX(),trY=tR.getY(),blx=bL.getX(),bly=bL.getY();
	int trx2=rhs.tR.getX(),trY2=rhs.tR.getY(),blx2=rhs.bL.getX(),bly2=rhs.bL.getY();
	if (trx>=trx2 && trY>=trY2 && blx<=blx2 && bly<=bly2)
		return 1;
	return 0;
}

int Rectangle::intersect(Rectangle rhs){
    if (rhs.tR.getX()<bL.getX() || tR.getX()<rhs.bL.getX())	// ranges of x don't overlap
    	return 0;
    if (rhs.tR.getY()<bL.getY() || tR.getY()<rhs.bL.getY())	// ranges of y don't overlap
    	return 0;
    return 1;
}

int Rectangle::inside(Circle c){
	if (c.contains(tR) && c.contains(bL))
		return 1;
	return 0;
}

int main(){
	Circle c1(Point2D(4,5),5),c2(Point2D(4,4),2);
	printf("area=%g perimeter=%g\nintersect=%d contains=%d\n", c1.area(),c1.perimeter(),c1.intersect(c2),c1.contains(c2));
	c2.set_radius(5);
	printf("intersect=%d contains=%d\n", c1.intersect(c2),c1.contains(c2));
	Rectangle r1(Point2D(6,9),Point2D(1,2)),r2(Point2D(4,4),Point2D(2,2));
	// printf("%d %d %d %d\n", r1.get_bL().getX(),r1.get_bL().getY(),r1.get_tR().getX(),r1.get_tR().getY());
	printf("area=%g perimeter=%g\nintersect=%d contains=%d\n", r1.area(),r1.perimeter(),r1.intersect(r2),r1.contains(r2));
	r2.set_tR(Point2D(10,12));
	printf("intersect=%d contains=%d\n", r1.intersect(r2),r1.contains(r2));
	//g g constructor suffix
	return 0;
}
