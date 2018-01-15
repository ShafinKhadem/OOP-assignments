#include <bits/stdc++.h>
using namespace std;

typedef enum {UNDEFINED, POINT2D, POINT3D, CIRCLE, SQUARE, RECTANGLE, SPHERE} STYPE;

class Shape
{
	STYPE type;
public:
	Shape();
	Shape(STYPE type);
	virtual void print();
	virtual double area();
	virtual bool contains(const Shape *s);
	//Intentionally made non-virtual
	bool operator==(const Shape &rhs);
	virtual ~Shape(){}
};

Shape::Shape()
{
	type = UNDEFINED;
}

Shape::Shape(STYPE argtype)
{
	type = argtype;
}

double Shape::area()
{
	cout << "I am a dummy Shape";
	return 0.0;
}

bool Shape::contains(const Shape *rhs)
{
	cout << "You see this, because appropriate contains function is undefined";
	return false;
}

void Shape::print()
{
	cout << "Type: " << type <<" ";
}

bool Shape::operator==(const Shape &rhs)
{
	if(type==rhs.type) return true;
	else return false;
}

class Point2D : virtual public Shape
{
protected:
	double x,y;
public:
	Point2D();
	Point2D(STYPE argtype, int argx, int argy);
	void print();
	double area();
	bool contains(const Shape * rhs);
	bool contains(const Point2D * rhs);
	bool operator==(const Point2D &rhs);
	double getX() const { return x; }
	double getY() const { return y; }
	~Point2D(){}
};

Point2D::Point2D() //calls Base's default constructor
{
	x = 0.0;
	y = 0.0;
}

Point2D::Point2D(STYPE argtype, int argx, int argy) : Shape(argtype)
{
	x = argx;
	y = argy;
}

void Point2D::print()
{
	Shape::print();
	cout << " (" << x << "," << y << ")";
}

double Point2D::area()
{
	return 0.0;
}

bool Point2D::contains(const Shape * s)
{
	const Point2D * pointType = dynamic_cast<const Point2D*>(s);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}
	//By default, use base, which will output that it's undefined XD
	return Shape::contains(s);
}

bool Point2D::contains(const Point2D * rhs)
{
	if(x==rhs->x && y==rhs->y) return true;
	else return false;
}

bool Point2D::operator==(const Point2D & rhs)
{
	if( !Shape::operator==(rhs) ) return false;
	if( x==rhs.x && y==rhs.y ) return true;
	else return false;
}

class Rectangle : public Shape
{
	Point2D topRight;
	Point2D bottomLeft;
public:
	Rectangle();//implement this
	Rectangle(STYPE type, Point2D tr, Point2D bl);//implement this
	void print(); //implement this
	double area(); //implement this
	bool contains(const Shape *rhs); //implement this to check containment for point2d only
	bool operator==(const Rectangle &rhs); //implement this
	~Rectangle(){}
	Point2D get_topRight() const{ return topRight; }
	Point2D get_bottomLeft () const{ return bottomLeft; }
};

Rectangle::Rectangle():
topRight(POINT2D,0,0),bottomLeft(POINT2D,0,0){}//to compare shapes type must be same

Rectangle::Rectangle(STYPE type, Point2D tr, Point2D bl):Shape(type){
	topRight=tr;bottomLeft=bl;
}

bool Rectangle::contains(const Shape *rhs){
	const Point2D *s=dynamic_cast<const Point2D*>(rhs);
	if (s->getX()>bottomLeft.getX() && s->getX()<topRight.getX() && s->getY()>bottomLeft.getY() && s->getY()<topRight.getY())
		return 1;
	return 0;
}

void Rectangle::print(){
	Shape::print();
	//cout<<"topRight= ";topRight.print();
	cout<<" bottomLeft= ";bottomLeft.print();
	cout<<" lengh= "<<topRight.getX()-bottomLeft.getX();
}

double Rectangle::area(){
	return (topRight.getX()-bottomLeft.getX())*(topRight.getY()-bottomLeft.getY());
}

bool Rectangle::operator==(const Rectangle &rhs){
	return topRight==rhs.topRight && bottomLeft==rhs.bottomLeft;
}


class Point3D : public Point2D
{
    double z;
public:
    Point3D(); //already implemented
    Point3D(STYPE type, double argx, double argy, double argz); //implement this
    void print(); //already implemented
    //double area(); Not needed, base version is sufficient
	double get_z () const{ return z; }
	~Point3D(){}
};

Point3D::Point3D()
{
    z = 0;
}

Point3D::Point3D(STYPE type, double argx, double argy, double argz):Point2D(type,argx,argy),Shape(type) {
	z=argz;
}

void Point3D::print()
{
	Shape::print();
    cout << " (" << getX() << "," << getY() << "," << z << ")";
}



class Shape3D : virtual public Shape
{
public:
	Shape3D();
	Shape3D(STYPE type);
	virtual double volume();
	virtual bool contains(const Point3D p){}
	~Shape3D(){}
};

Shape3D::Shape3D()
{

}

Shape3D::Shape3D(STYPE argtype) : Shape(argtype)
{

}

double Shape3D::volume()
{
	cout << "You see this, because appropriate function is missing in the derived class\n";
	return 0.0;
}

class Circle3D : public Shape3D
{
	Point3D center;
	double radius;
public:
	Circle3D();
	Circle3D(STYPE type, Point3D c, double r); //implement this
	double area(); //implement this
	double volume(){return 0;};
	void print(); //implement this
	bool contains(const Point3D p); //implement this
	~Circle3D(){}
};

Circle3D::Circle3D():
center(POINT3D,0,0,0),radius(0){}

Circle3D::Circle3D(STYPE type, Point3D c, double r):Shape(type) {
	center=c;radius=r;
}

double Circle3D::area(){
	return 2*3.1416*radius*radius;
}

void Circle3D::print(){
	Shape::print();
	cout<<"center= ";center.print();
	cout<<" radius= "<<radius;
}

bool Circle3D::contains(const Point3D s){
	if ((pow((s.getX()-center.getX()),2)+pow((s.getY()-center.getY()),2)<pow(radius,2)) && s.get_z()==center.get_z()){
		return 1;
	}
	return 0;
}

class Square : public Rectangle
{

    public:
        Square(){}
        Square(Point2D p, int len):Rectangle(RECTANGLE,Point2D(POINT2D,p.getX()+len,p.getY()+len),p){}
        ~Square(){}
    protected:

};


int main()
{
    Point3D p1(POINT3D,5,5,5);
    Point3D p3(POINT3D,7,7,7);
    Shape3D * s3d = new Circle3D(CIRCLE,p1, (double)10);
    cout << s3d->area()<<endl;
    cout << s3d->volume()<<endl; //should print 0
    cout << s3d->contains(p3)<<endl;
    Point2D p(POINT2D,10,10);
    Shape *p2=new Point2D(POINT2D,7,7);
    Shape * s = new Square(p, 20);
    s->print(); //should print bottom-left point and side-length
    cout <<endl << s->area()<<endl;
    cout << s->contains(p2)<<"\n";
}
