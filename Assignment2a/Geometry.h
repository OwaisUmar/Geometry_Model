#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <vector>
#include <memory>

class Point; // forward declaration

class Shape {

public:
	Shape();
	
	Shape(int d);

	virtual bool setDepth(int d) = 0;
	virtual int getDepth() const = 0;
	virtual int dim() const = 0;
	virtual void translate(float x, float y) = 0;
	virtual void rotate() = 0;
	virtual void scale(float f) = 0;
	virtual bool contains(const Point& p) const = 0;

	static constexpr double PI = 3.1415926;

protected:
	int depth;	//to store the depth of the object
};

class Point final : public Shape {

public:
	Point(float x, float y, int d = 0);
	
	bool setDepth(int d) override final;
	int getDepth() const override final;
	int dim() const override final;
	void translate(float x, float y) override final;
	void rotate() override final;
	void scale(float f) override final;
	bool contains(const Point& p) const override final;

	float getX() const;
	float getY() const;

private:
	float X;	//to store the x-coordinate of the point 
	float Y;	//to store the y-coordinate of the point
};

class LineSegment final: public Shape {

public:
	LineSegment(const Point& p, const Point& q);

	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;
	float length() const;

	bool setDepth(int d) override final;
	int getDepth() const override final;
	int dim() const override final;
	void translate(float x, float y) override final;
	void rotate() override final;
	void scale(float f) override final;
	bool contains(const Point& p) const override final;

private:
	//variables to store the endpoints of the line segment
	Point P = Point(0,0);
	Point Q = Point(0,0);
};

class TwoDShape : public Shape {

public:
	TwoDShape();

	TwoDShape(int d);
	
	int dim() const override final;
	
	virtual float area() const = 0;
};

class Rectangle final : public TwoDShape {

public:
	Rectangle(const Point& p, const Point& q);

	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;

	float area() const override;

	bool setDepth(int d) override final;
	int getDepth() const override final;
	void translate(float x, float y) override final;
	void rotate() override final;
	void scale(float f) override final;
	bool contains(const Point& p) const override final;

private:
	//variables to store the corner points of the rectangle
	Point P = Point(0,0);
	Point Q = Point(0,0);

	//functions to get the width and height of the rectangle
	float get_width() const;	
	float get_height() const;
};

class Circle final : public TwoDShape {

public:
	Circle(const Point& c, float r);

	float getX() const;
	float getY() const;
	float getR() const;

	float area() const override final;

	bool setDepth(int d) override final;
	int getDepth() const override final;
	void translate(float x, float y) override final;
	void rotate() override final;
	void scale(float f) override final;
	bool contains(const Point& p) const override final;

private:
	Point centre = Point(0,0);	//to store the centre coordinates of the circle
	float radius;				//to store the radius of the circle
};


class Scene {

public:
	Scene();
	
	void addObject(std::shared_ptr<Shape> ptr);

	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:
	std::vector<std::shared_ptr<Shape>> pointersVector;	//vector to store the shared pointers
	int drawDepth = -1;									//to specify the drawing depth

friend std::ostream& operator<<(std::ostream& out, const Scene& s);

};

#endif /* GEOMETRY_H_ */