#include<iostream>
#include <cmath>
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
	cout<<"topRight= ";topRight.print();
	cout<<" bottomLeft= ";bottomLeft.print();
}

double Rectangle::area(){
	return (topRight.getX()-bottomLeft.getX())*(topRight.getY()-bottomLeft.getY());
}

bool Rectangle::operator==(const Rectangle &rhs){
	return topRight==rhs.topRight && bottomLeft==rhs.bottomLeft;
}


class Circle : public Shape
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(STYPE type, Point2D c, double r); //implement this
	double area(); //implement this
	void print(); //implement this
	bool contains(const Shape * s); //implemented partially
	bool contains(const Point2D * p); //implement this
	bool contains(const Circle * rhs); //implement this
	bool contains(const Rectangle * p); //implement this
	bool operator==(const Circle &rhs); //implement this
	~Circle(){}
};

Circle::Circle():
center(POINT2D,0,0),radius(0){}

Circle::Circle(STYPE type, Point2D c, double r):Shape(type) {
	center=c;radius=r;
}

double Circle::area(){
	return 3.1416*radius*radius;
}

void Circle::print(){
	Shape::print();
	cout<<"center= ";center.print();
	cout<<" radius= "<<radius;
}

bool Circle::contains(const Point2D * s){
	if ((pow((s->getX()-center.getX()),2)+pow((s->getY()-center.getY()),2))<pow(radius,2)){
		return 1;
	}
	return 0;
}

bool Circle::contains(const Circle * s){
	double disCen=sqrt((pow((center.getX()-s->center.getX()),2)+pow((center.getY()-s->center.getY()),2)));
	if (disCen<(radius-s->radius)){
		return 1;
	}
	return 0;
}

bool Circle::contains(const Rectangle * p){
	const Point2D s1=(p->get_topRight()),s2=p->get_bottomLeft();
	if (contains(&s1) && contains(&(s2)))
		return 1;
	return 0;
}

bool Circle::contains(const Shape * s)
{
	const Point2D * pointType = dynamic_cast<const Point2D*>(s);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}
	const Circle * circleType = dynamic_cast<const Circle*>(s);
	if(circleType!=NULL)
	{
		//Supported
		return contains(circleType);
	}
	const Rectangle * rectangleType = dynamic_cast<const Rectangle*>(s);
	if(rectangleType!=NULL)
	{
		//Supported
		return contains(rectangleType);
	}
	//By default
	return Shape::contains(s);
}

bool Circle::operator==(const Circle &rhs){
	return center==rhs.center && radius==rhs.radius;
}


class Shape3D : virtual public Shape
{
public:
	Shape3D();
	Shape3D(STYPE type);
	virtual double volume();
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


class Point3D : public Point2D,public Shape3D
{
    double z;
public:
    Point3D(); //already implemented
    Point3D(STYPE type, double argx, double argy, double argz); //implement this
    void print(); //already implemented
    //double area(); Not needed, base version is sufficient
	bool contains(const Shape *rhs); //implement this
	bool contains(const Point3D *rhs);  //implement this
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

bool Point3D::contains(const Shape *rhs){
	const Point3D * pointType = dynamic_cast<const Point3D*>(rhs);
	if(pointType!=NULL) 
	{
		//Supported
		return contains(pointType);
	}
	//By default, use base, which will output that it's undefined XD
	return Shape::contains(rhs);
}

bool Point3D::contains(const Point3D * rhs)
{
	if(x==rhs->x && y==rhs->y && z==rhs->z) return true;
	else return false;
}



class Sphere : public Shape3D
{
	Point3D center;
	double radius;
public:
	Sphere();//implement this
	Sphere(STYPE type, Point3D c, double r);//implement this
	void print(); //implement this
	double area(); //implement this
	double volume(); //implement this
	bool contains(const Shape * rhs); //implement this for checking containgment of Point3D, Sphere inside sphere
	bool contains(const Point3D * p); //implement this
	bool contains(const Sphere * s); //implement this
	~Sphere(){}
};

Sphere::Sphere():
center(POINT3D,0,0,0),radius(0){}

Sphere::Sphere(STYPE type, Point3D c, double r):Shape3D(type){
	center=c;radius=r;
}

void Sphere::print(){
	Shape3D::print();
	cout<<"center= ";center.print();
	cout<<" radius= "<<radius;
}

double Sphere::area(){
	return 4*3.1416*radius*radius;
}

double Sphere::volume(){
	return 4*3.1416*radius*radius*radius/3;
}

bool Sphere::contains(const Point3D *p){
	const Point3D *s=dynamic_cast<const Point3D*>(p);
	if ((pow((s->getX()-center.getX()),2)+pow((s->getY()-center.getY()),2)+pow((s->get_z()-center.get_z()),2))<pow(radius,2)){
		return 1;
	}
	return 0;
}

bool Sphere::contains(const Sphere * s){
	double disCen=sqrt(pow((center.getX()-s->center.getX()),2)+pow((center.getY()-s->center.getY()),2)+pow((center.get_z()-s->center.get_z()),2));
	if (disCen<(radius-s->radius)){
		return 1;
	}
	return 0;
}

bool Sphere::contains(const Shape * rhs){
	const Point3D * pointType = dynamic_cast<const Point3D*>(rhs);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}
	const Sphere * SphereType = dynamic_cast<const Sphere*>(rhs);
	if(SphereType!=NULL)
	{
		//Supported
		return contains(SphereType);
	}
	//By default
	return Shape3D::contains(rhs);
}


int main(void)
{
	//Write main function to demonstrate your code
	//Create circles, rectangels, point2d,point3d,and sphere objects using base class pointers
	//then call the virtual methods to show that polymorphism works!
	while(1)
	{
		int choice = 10;
		Shape * shape;
		Shape3D * shape3D;
		cout << "1. Point2D 2. Rectangle 3. Circle\n";
		cout << "4. Point3D 5. Sphere. 0. Exit\n";
		cout << "Your choice:";
		cin >> choice;
		switch(choice)
		{
			case 1:
				shape = new Point2D(POINT2D, 5.0,10.0);
				shape->print();
				cout << "\nArea: " << shape->area()<<"\n";
				break;
			case 2:
			{
				Point2D p1(POINT2D,5.0,5.0);
				Point2D p2(POINT2D,20.0,20.0);
				shape = new Rectangle(RECTANGLE, p1, p2);
				shape->print();
				cout << "\nArea: " << shape->area() <<"\n";
				break;
			}
			case 3:
			{
				Point2D p1(POINT2D,0.0,0.0);
				shape = new Circle(CIRCLE,p1,10.0);
				shape->print();
				cout << "\nArea: " << shape->area()<<"\n";
				break;
			}
			case 4:
			{
				shape3D = new Point3D(POINT3D,5.0,10.0,20.0);;
				shape3D->print();
				cout << "\nArea: " << shape3D->area()<<"\n";
				cout << "\nVolume: " << shape3D->volume()<<"\n";
				break;
			}
			case 5:
			{
				Point3D p1(POINT3D,0.0,0.0,0.0);
				shape3D = new Sphere(SPHERE,p1,10.0);
				shape3D->print();
				cout << "\nArea: " << shape3D->area();
				cout << "\nVolume: " << shape3D->volume()<<"\n";
				break;
			}
		}
		if(choice==0.0)break;
		else cout<<"\n";
	}
	//add other functions for demonstration
	Sphere sp(SPHERE,Point3D(POINT3D, 5,10,20),10.0);
	Shape *p=new Point3D(POINT3D,6,5,18);
	cout<<"Sphere sp contains Point3D *p: "<<sp.contains(p)<<"\n";
	Sphere *sp2=new Sphere(SPHERE,Point3D(POINT3D, 6,5,18),4);
	cout<<"sp contains Sphere *sp2: "<<sp.contains(sp2)<<"\n";
	//circle(point,circle, rectangle)
	p=new Point2D(POINT2D,5,10);
	Shape *r=new Rectangle(RECTANGLE,Point2D(POINT2D,10,12),Point2D(POINT2D,3,5));
	cout<<"Rectangle *r contains Point2D *p: "<<r->contains(p)<<"\n";
	delete p;p=new Circle(CIRCLE,Point2D(POINT2D,5,6),20);
	cout<<"Circle *p contaiins *r: "<<p->contains(r)<<"\n";
	delete p,sp2,r;
	return 0;
}