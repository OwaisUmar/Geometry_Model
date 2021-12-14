#include<vector>
#include "Geometry.h"

// ============ Shape class =================

Shape::Shape() {}

Shape::Shape(int d) {
	if(d<0) 
		throw std::invalid_argument("Depth cannot be negative");
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d), X(x), Y(y) {
	setDepth(d);
}

bool Point::setDepth(int d) {
	if(d<0)
		return false;
	depth = d;	
	return true;
}

int Point::getDepth() const {
	return depth;
}

int Point::dim() const {
	return 0;
}

void Point::translate(float x, float y) {
	X = X+x;
	Y = Y+y;
}

void Point::rotate() {}

void Point::scale(float f) {
	if(f <= 0)
		throw std::invalid_argument("f can't be zero");
}

bool Point::contains(const Point& p) const {
	if(p.getX() == X && p.getY() == Y)
		return true;
	return false;
}


float Point::getX() const {
	return X;
}

float Point::getY() const {
	return Y;
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) {
	if(p.getDepth() != q.getDepth())
		throw std::invalid_argument("Different depths not allowed");
	if(p.getX() == q.getX() && p.getY()==q.getY())
		throw std::invalid_argument("Same coordinates not allowed");
	if(p.getX() != q.getX() && p.getY()!=q.getY())
		throw std::invalid_argument("Line is not axis aligned");
	P = p;
	Q = q;
	setDepth(p.getDepth());
}

float LineSegment::getXmin() const {
	return(std::min(P.getX(), Q.getX()));
}

float LineSegment::getXmax() const {
	return(std::max(P.getX(), Q.getX()));
}

float LineSegment::getYmin() const {
	return(std::min(P.getY(), Q.getY()));
}

float LineSegment::getYmax() const {
	return(std::max(P.getY(), Q.getY()));
}

float LineSegment::length() const {
	return (getXmax()-getXmin()) + (getYmax()-getYmin());
}

bool LineSegment::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;
	return true;	
}

int LineSegment::getDepth() const {
	return depth;
}

int LineSegment::dim() const {
	return 1;
}

void LineSegment::translate(float x, float y) {
	P.translate(x,y);
	Q.translate(x,y);
}

void LineSegment::rotate() {
	float halfLen = length()/2;		//half length of the line segment
	if(P.getX() == Q.getX()) {
		P = Point((P.getX()+halfLen), (P.getY()+halfLen));
		Q = Point((Q.getX()-halfLen), (P.getY()));
	}
	else {
		P = Point((P.getX()+halfLen), (P.getY()+halfLen));
		Q = Point((P.getX()), (Q.getY()-halfLen));
	}
}

void LineSegment::scale(float f) {
	if(f<=0)
		throw std::invalid_argument("f can't be zero.");
	
	float len = length();		//length of the line segment
	float a = (len/2)*(f-1);	//to add/subtract for scaling

	if(P.getX() == Q.getX()) {
		P=Point(P.getX(), getYmax()+a);
		Q=Point(Q.getX(), getYmin()-a);	
	}
	else {
		P=Point(getXmax()+a, P.getY());
		Q=Point(getXmin()-a, Q.getY());
	}
}

bool LineSegment::contains(const Point& p) const {
	if(p.getX()>=getXmin() && p.getX()<=getXmax() && p.getY()>=getYmin() && p.getY()<=getYmax())
		return true;
	return false;
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape() {}

TwoDShape::TwoDShape(int d) : Shape(d) {}

int TwoDShape::dim() const {
	return 2;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	if(p.getDepth() != q.getDepth())
		throw std::invalid_argument("Different depths not allowed");
	if(p.getX()==q.getX() && p.getY()==q.getY())
		throw std::invalid_argument("Same coordinates not allowed");
	if(p.getX()==q.getX() || p.getY()==q.getY())
		throw std::invalid_argument("Points can't be on the same horizontal/vertical line");
	P = p;
	Q = q;
	setDepth(p.getDepth());
}

float Rectangle::getXmin() const {
	return(std::min(P.getX(), Q.getX()));
}

float Rectangle::getYmin() const {
	return(std::min(P.getY(), Q.getY()));
}

float Rectangle::getXmax() const {
	return(std::max(P.getX(), Q.getX()));
}

float Rectangle::getYmax() const {
	return(std::max(P.getY(), Q.getY()));
}

float Rectangle::get_width() const {
	return(getXmax()-getXmin());
}

float Rectangle::get_height() const {
	return(getYmax()-getYmin());
}

float Rectangle::area() const {
	return (get_width()*get_height());
}

bool Rectangle::setDepth(int d) {
	if(d<0)
		return false;
	depth = d;	
	return true;
}

int Rectangle::getDepth() const {
	return depth;
}

void Rectangle::translate(float x, float y) {
	P.translate(x,y);
	Q.translate(x,y);
}

void Rectangle::rotate() {
	float diff=(get_width()-get_height())/2;	

	//new coordinates after rotating:
	float newXmax=getXmax()-diff;
	float newXmin=getXmin()+diff;
	float newYmax=getYmax()+diff;
	float newYmin=getYmin()-diff;

	//putting the new coordinates in the right place:
	if(P.getX() == getXmax() && P.getY() == getYmax()) {
		P = Point(newXmax, newYmax);
		Q = Point(newXmin, newYmin);
	}
	else if(P.getX() == getXmax() && P.getY() == getYmin()) {
		P = Point(newXmax, newYmin);
		Q = Point(newXmin, newYmax);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmax()) {
		P = Point(newXmin, newYmax);
		Q = Point(newXmax, newYmin);
	}
	else {
		P = Point(newXmin, newYmin);
		Q = Point(newXmax, newYmax);
	}
}

void Rectangle::scale(float f) {
	if(f<=0)
		throw std::invalid_argument("f can't be zero.");

	//to add/subtract for scaling
	float a = (get_width()/2) * (f-1);
	float b = (get_height()/2) * (f-1);

	//temp variables to hold the values of P and Q
	Point temp_P = P;
	Point temp_Q = Q;
	if(P.getX() == getXmax() && P.getY() == getYmax()) {
		temp_P = Point(P.getX()+a, P.getY()+b);
		temp_Q = Point(Q.getX()-a, Q.getY()-b);
	}
	else if(P.getX() == getXmax() && P.getY() == getYmin()) {
		temp_P = Point(P.getX()+a, P.getY()-b);
		temp_Q = Point(Q.getX()-a, Q.getY()+b);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmax()) {
		temp_P = Point(P.getX()-a, P.getY()+b);
		temp_Q = Point(Q.getX()+a, Q.getY()-b);
	}
	else {
		temp_P = Point(P.getX()-a, P.getY()-b);
		temp_Q = Point(Q.getX()+a, Q.getY()+b);
	}
	P = temp_P;
	Q = temp_Q;
}

bool Rectangle::contains(const Point& p) const {
	if(p.getX()>=getXmin() && p.getX()<=getXmax() && p.getY()>=getYmin() && p.getY()<=getYmax())
		return true;
	return false;
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
	if(r<=0)
		throw std::invalid_argument("Radius cannot be 0 or negative");
	radius = r;
	centre = c;
	setDepth(c.getDepth());
}

float Circle::getX() const {
	return centre.getX();
}

float Circle::getY() const {
	return centre.getY();
}

float Circle::getR() const {
	return radius;
}

float Circle::area() const {
	return (PI*radius*radius);
}

bool Circle::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;	
	return true;
}

int Circle::getDepth() const {
	return depth;
}

void Circle::translate(float x, float y) {
	centre.translate(x, y);
}

void Circle::rotate() {}

void Circle::scale(float f) {
	if(f<=0)
		throw std::invalid_argument("f can't be zero.");
	radius = radius*f;
}

bool Circle::contains(const Point& p) const {
	if((centre.getX()-p.getX())*(centre.getX()-p.getX()) + (centre.getY()-p.getY())*(centre.getY()-p.getY()) <= radius*radius)
		return true;
	return false;
}

// ================= Scene class ===================

Scene::Scene() {}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	pointersVector.push_back(ptr);	
}

void Scene::setDrawDepth(int depth) {
	drawDepth=depth;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	int x=0, y=s.HEIGHT-1;		//coordinates of drawing canvas
	while(y>=0) {
		int flag=0;
		for(auto i:s.pointersVector) { 
			if(i->contains(Point(x, y)) && (i->getDepth()<=s.drawDepth || s.drawDepth==-1)) {
				out<<'*';
				flag=1;
				break;
			}
		}	
		if(!flag)
			out<<" ";
		x++;
		if(x==s.WIDTH) {
			out<<std::endl;
			x=0;
			y--;
		}
	}		
	return out;
}