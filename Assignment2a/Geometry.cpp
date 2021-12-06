#include<math.h>
#include<vector>
#include "Geometry.h"
using namespace std;

// ============ Shape class =================

Shape::Shape(int d) {
	if(d<0) 
		throw invalid_argument("Depth cannot be negative.\n");
}

// =============== Point class ================

Point::Point(float x, float y, int d) {
	X=x;
	Y=y;
	setDepth(d);
	dimension=0;
}

bool Point::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;	
}

int Point::getDepth() const {
	return depth;
}

int Point::dim() const {
	return dimension;
}

void Point::translate(float x, float y) {
	X=X+x;
	Y=Y+y;
}

void Point::rotate() {

}

void Point::scale(float f) {
	
}

bool Point::contains(const Point& p) const {
	if(p.getX()==X && p.getY()==Y)
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
	if(p.getDepth()!=q.getDepth())
		throw invalid_argument("Different depths not allowed");
	if(p.getX()==q.getX() && p.getY()==q.getY())
		throw invalid_argument("Same coordinates not allowed");
	if(p.getX()!=q.getX() || p.getY()!=q.getY())
		throw invalid_argument("Line is not axis aligned");
	P=p;
	Q=q;
	dimension=1;
}



float LineSegment::getXmin() const {
	return(min(P.getX(), Q.getX()));
}

float LineSegment::getXmax() const {
	return(max(P.getX(), Q.getX()));
}

float LineSegment::getYmin() const {
	return(min(P.getY(), Q.getY()));
}

float LineSegment::getYmax() const {
	return(max(P.getY(), Q.getY()));
}

float LineSegment::length() const {
	if(P.getX()==P.getX())
		return abs(P.getY()-Q.getY());
	else	
		return abs(P.getX()-Q.getX());
}

bool LineSegment::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;	
}

int LineSegment::getDepth() const {
	return depth;
}

int LineSegment::dim() const {
	return dimension;
}

void LineSegment::translate(float x, float y) {
	P.translate(x, y);
	Q.translate(x, y);
}

void LineSegment::rotate() {
	if(P.getX()==Q.getX()) {
		float diff=(getYmax()-getYmin())/2;
		P=Point((P.getX()+diff), (P.getY()+diff));
		Q=Point((Q.getX()-diff), (P.getY()+diff));
	}
	else if(P.getY()==Q.getY()) {
		float diff=(getXmax()-getXmin())/2;
		P=Point((P.getX()+diff), (P.getY()+diff));
		Q=Point((Q.getX()+diff), (P.getY()-diff));
	}
}

void LineSegment::scale(float f) {
	if(f<=0)
		throw invalid_argument("f can't be zero.");
	if(P.getX()==Q.getX()) {
		float dist=(getYmax()-getYmin());
		float a=(dist/2)*(f-1);
		P=Point(P.getX(), getYmax()+a);
		Q=Point(Q.getX(), getYmin()-a);
		
	}
	else if(P.getY()==Q.getY()) {
		float dist=(getXmax()-getXmin());
		float a=(dist/2)*(f-1);
		P=Point(getXmax()+a, P.getY());
		Q=Point(getXmin()-a, Q.getX());
	}
}

bool LineSegment::contains(const Point& p) const {
	if(p.getX()>=getXmin() && p.getX()<=getXmax() && p.getY()>=getYmin() && p.getY()<=getYmax())
		return true;
	return false;
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(){}

TwoDShape::TwoDShape(int d) {
	depth=d;
	dimension=2;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	if(p.getDepth()!=q.getDepth())
		throw invalid_argument("Different depths not allowed");
	if(p.getX()==q.getX() && p.getY()==q.getY())
		throw invalid_argument("Same coordinates not allowed");
	if(p.getX()==q.getX() || p.getY()==q.getY())
		throw invalid_argument("Points can't be on the same horizontal/vertical line");
	P=p;
	Q=q;
}

float Rectangle::getXmin() const {
	return(min(P.getX(), Q.getX()));
}

float Rectangle::getYmin() const {
	return(min(P.getY(), Q.getY()));
}

float Rectangle::getXmax() const {
	return(max(P.getX(), Q.getX()));
}

float Rectangle::getYmax() const {
	return(max(P.getY(), Q.getY()));
}

float Rectangle::area() const {
	return(abs((P.getX()-Q.getX())*(P.getY()-Q.getY())));
}

bool Rectangle::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;	
}

int Rectangle::getDepth() const {
	return depth;
}

int Rectangle::dim() const {
	return dimension;
}

void Rectangle::translate(float x, float y) {
	P.translate(x, y);
	Q.translate(x, y);
}

void Rectangle::rotate() {
	float W=getXmax()-getXmin();	//Width of rectangle
	float H=getYmax()-getYmin();	//Height of rectangle
	float diff=(W-H)/2;
	float newXmax=getXmax()-diff;
	float newXmin=getXmin()+diff;
	float newYmax=getYmax()+diff;
	float newYmin=getYmin()-diff;
	if(P.getX() == getXmax() && P.getY() == getYmax()) {
		P=Point(newXmax, newYmax);
		Q=Point(newXmin, newYmin);
	}
	else if(P.getX() == getXmax() && P.getY() == getYmin()) {
		P=Point(newXmax, newYmin);
		Q=Point(newXmin, newYmax);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmax()) {
		P=Point(newXmin, newYmax);
		Q=Point(newXmax, newYmin);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmin()) {
		P=Point(newXmin, newYmin);
		Q=Point(newXmax, newYmax);
	}
}


void Rectangle::scale(float f) {
	if(f<=0)
		throw invalid_argument("f can't be zero.");
	float W=getXmax()-getXmin();
	float H=getYmax()-getYmin();		
	float a=(W/2)*(f-1);
	float b=(H/2)*(f-1);
	if(P.getX() == getXmax() && P.getY() == getYmax()) {
		P=Point(P.getX()+a, P.getY()+b);
		Q=Point(P.getX()-a, P.getY()-b);
	}
	else if(P.getX() == getXmax() && P.getY() == getYmin()) {
		P=Point(P.getX()+a, P.getY()-b);
		Q=Point(P.getX()-a, P.getY()+b);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmax()) {
		P=Point(P.getX()-a, P.getY()+b);
		Q=Point(P.getX()+a, P.getY()-b);
	}
	else if(P.getX() == getXmin() && P.getY() == getYmin()) {
		P=Point(P.getX()-a, P.getY()-b);
		Q=Point(P.getX()+a, P.getY()+b);
	}
}

bool Rectangle::contains(const Point& p) const {
	if(p.getX()>=getXmin() && p.getX()<=getXmax() && p.getY()>=getYmin() && p.getY()<=getYmax())
		return true;
	return false;
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
	if(r<=0)
		throw invalid_argument("Radius cannot be 0 or negative");
	radius=r;
	centre=c;
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
	return(PI*radius*radius);
}

bool Circle::setDepth(int d) {
	if(d<0)
		return false;
	depth=d;	
}

int Circle::getDepth() const {
	return depth;
}

int Circle::dim() const {
	return dimension;
}

void Circle::translate(float x, float y) {
	centre.translate(x, y);
}

void Circle::rotate() {
}


void Circle::scale(float f) {
	radius=radius*f;
}

bool Circle::contains(const Point& p) const {
	if((centre.getX()-p.getX())*(centre.getX()-p.getX()) + (centre.getY()-p.getY())*(centre.getY()-p.getY()) <= radius*radius)
		return true;
	return false;
}


// ================= Scene class ===================

Scene::Scene() {
	// IMPLEMENT ME
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	V.push_back(ptr);	
}

void Scene::setDrawDepth(int depth) {
	Depth=depth;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	for(auto i : s.V) {
		
	}
		
	return out;
}
