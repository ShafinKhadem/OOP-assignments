#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;



class Point2D
{
	double x,y;
public:
	Point2D(){ x=0; y=0; }
	Point2D(double x, double y);
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	void print();
	Point2D operator+(Point2D p2){return Point2D(x+p2.x,y+p2.y);}
	Point2D operator*(double n){ return Point2D(x*n,y*n); }
	bool operator==(Point2D p2){ return x==p2.x && y==p2.y; }
	bool operator!=(Point2D p2){ return !(x==p2.x && y==p2.y); }
	~Point2D(){ x = 0; y = 0; }
};

Point2D::Point2D(double argx,double argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(double argx)
{
	x=argx;
}

void Point2D::setY(double argy)
{
	y = argy;
}

double Point2D::getX()
{
	return x;
}

double Point2D::getY()
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
	void set_centerX(double _centerX){ center.setX(_centerX); }
	void set_centerY(double _centerY){ center.setY(_centerY); }
	void set_radius(double _radius){ radius=_radius; }
	double area(){ return 3.1416*radius*radius; }
	void print();
	int intersect(Circle rhs);
	int contains(Circle rhs);
	int contains(Point2D p);
	double perimeter(){ return 2*3.1416*radius; }
	Circle operator+(Point2D p){ return Circle(center+p,radius); }
	Circle operator*(double n){ return Circle(center*n,radius*n); }
	Circle operator+(Circle c2){
		return Circle(center*(radius/(radius+c2.radius))+c2.center*(c2.radius/(radius+c2.radius)),radius+c2.radius);
	}
	Circle operator-(Circle c2);
	bool operator==(Circle c2){ return fabs(area()-c2.area())<.000000001; }
	bool operator>(Circle c2){ return area()>c2.area(); }
	bool operator>=(Circle c2){ return area()>=c2.area(); }
	bool operator<(Circle c2){ return area()<c2.area(); }
	bool operator<=(Circle c2){ return area()<=c2.area(); }
	Circle operator++(){ radius++; return *this; }
	Circle operator++(int faltu);
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
	if ((pow((p.getX()-center.getX()),2)+pow((p.getY()-center.getY()),2))<pow(radius,2)){
		return 1;
	}
	return 0;
}

void Circle::print(){
	cout<<"Center: ";
	center.print();
	cout<<"  Radius: "<<radius<<'\n';
}

Circle Circle::operator-(Circle c2){
	if(radius>=c2.radius)
		return Circle(center*(radius/(radius+c2.radius))+c2.center*(c2.radius/(radius+c2.radius)),radius-c2.radius);
	else{
		printf("\nERROR: RADIUS CAN'T BE NEGATIVE :)\n\n");
		return *this;
	}
}

Circle Circle::operator++(int faltu){
	Circle temp=(*this);
	radius++;
	return temp;
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
	void set_tRX(double _tRX){ tR.setX(_tRX); }
	void set_tRY(double _tRY){ tR.setY(_tRY); }
	void set_bLX(double _bLX){ bL.setX(_bLX); }
	void set_bLY(double _bLY){ bL.setY(_bLY); }
	double area(){ return (tR.getX()-bL.getX())*(tR.getY()-bL.getY()); }
	double perimeter(){ return 2*(tR.getX()-bL.getX())+2*(tR.getY()-bL.getY()); }
	int contains(Rectangle rhs);
	int intersect(Rectangle rhs);
	int inside(Circle c);
	Rectangle operator+(Point2D p){return Rectangle(tR+p,bL+p);}
	Rectangle operator*(double n){return Rectangle(tR*n,bL*n);}
	void print();
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
    if (contains(rhs) || rhs.tR.getX()<bL.getX() || rhs.bL.getX()>tR.getX())
    	return 0;
    if (rhs.contains(*this) || bL.getY()>rhs.tR.getY() || rhs.bL.getY()>tR.getY())
    	return 0;
    return 1;
}

int Rectangle::inside(Circle c){
	if (c.contains(tR) && c.contains(bL))
		return 1;
	return 0;
}

void Rectangle::print(){
	cout<<"topRight: ";
	tR.print();
	cout<<" bottomLeft: ";
	bL.print();
	cout<<'\n';
}

int main(){
	Circle c1(Point2D(4,5),5),c2(Point2D(4,4),2);
	Rectangle r1(Point2D(6,9),Point2D(1,2));
	Point2D(4,6)==Point2D(4,6)? printf("equal\n"):printf("not equal\n");
	Point2D(6,6)==Point2D(4,6)? printf("equal\n"):printf("not equal\n");
	(Point2D(2,6)*2)!=Point2D(4,6)? printf("not equal\n"):printf("equal\n");
	c2=c2+Point2D(5,1);
	c2.print();
	c1=c1*2;
	c1.print();
	c1=c1-c2;
	c1.print();
	c1=c1+c2;
	c1.print();
	c1>c2? printf("larger\n"):printf("not larger\n");
	c2.set_radius(c1.getRadius());
	c1==c2? printf("equal\n"):printf("not equal\n");
	c1>c2? printf("larger\n"):printf("not larger\n");
	c1>=c2? printf("larger or equal\n"):printf("smaller\n");
	c1.set_radius(1);
	c1<=c2? printf("smaller or equal\n"):printf("larger\n");
	c1<c2? printf("smaller\n"):printf("not smaller\n");
	c1=c1-c2;
	c1.print();
	(c1++).print();
	(++c1).print();
	r1=r1+Point2D(2,3);
	r1.print();
	r1=r1*2;
	r1.print();

	return 0;
}