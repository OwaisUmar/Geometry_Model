# Coordinate Geometry Model

### Overview and the class hierarchy
A number of different classes are used to model different geometric shapes, all
derived from a common base class called Shape. The class hierarchy is as shown in
this diagram:

![image](https://user-images.githubusercontent.com/62874437/206720005-07f63255-a7b3-4c9a-88f1-a6d31c73845e.png)


In addition to attributes specific to each type of objects, all objects have a "depth".
The *depth* of an object is a non-negative integer indicating which "layer" or "plane"
it is in: imagine that there are multiple "planes" in the coordinate system, or like
"layers" in some photo-editing software; see figure below.

![image](https://user-images.githubusercontent.com/62874437/206720926-cc8e6755-a409-4b4d-b4fd-a8eddfd992e5.png)


### Constructors of Shape and its subclasses

The following explains each of the classes and their constructors:
- Shape(int d):
This is the base class and should be abstract (no object of this class should
be constructed). Nevertheless, it has a constructor with a parameter d
specifying the depth of the object. If d is negative, the constructor should
throw a std::invalid_argument exception.
- Point(float x, float y, int d=0):
This class models a point, which is a zero-dimensional object specified by its
x-coordinate, y-coordinate and its depth. The =0 here indicates that d is a
default argument, namely that it will by default set to 0 if it is not supplied
when the constructor is invoked.
- LineSegment(const Point& p, const Point& q):
This class models a line segment, which is a one-dimensional object, the
portion of a straight line passing between the two points. Here we model
"axis-aligned" line segments only, i.e. the line segment must be parallel to
either the x-axis or the y-axis. The constructor specifies the two endpoints of
the line segment. The two points p and q are not necessarily given in any
order; the line segment has no "direction". The two endpoints should have
the same depth, and the resulting line segment has a depth equal to that of
its endpoints. If the two endpoints have different depths, or if both their xand y-coordinates are different (line not horizontal/vertical), or if both their
x- and y-coordinates are the same (the two endpoints coincide), the
constructor should throw a std::invalid_argument exception.
- TwoDShape(int d):
The class models any two-dimensional object, and should be an abstract
class. The parameter d specifies the depth of the object.
- Rectangle(const Point& p, const Point& q):
This class models a rectangle, which is a two-dimensional object specified by
two opposite corners (not adjacent corners) p and q. Note that the two
points could be either the top-left and bottom-right corners, or the top-right
and bottom-left corners; and in no particular order. Only axis-aligned
rectangles are allowed, which means all edges are parallel to either the x- or
y-axis; thus two corners are sufficient to define a rectangle. For example, if
two of the corners are (1,2) and (3,4), then the other two corners must be
(3,2) and (1,4).
The two points p and q should have the same depth which is also the depth
of the rectangle. If the two given points have different depths, or have the
same x-coordinate and/or y-coordinate (which means they are on the same
horizontal/vertical line or are even the same point, and no rectangle can be
formed), the constructor should throw a std::invalid_argument exception.
- Circle(const Point& c, float r):
This models a circle, specified by its centre point c and its radius r. The depth
of the circle is the same as that of c. If the radius is 0 or negative, the
constructor should throw a std::invalid_argument exception.

### Other functions of Shape and its subclasses
The Shape class (and all its subclasses) should support the following functions:
- int getDepth()
bool setDepth(int d)
Get/set the depth of the object. If d is negative, return false and do not
update the depth.
- int dim():
Return the dimension (0, 1 or 2) of the object.
- void translate(float x, float y):
Translate, i.e. move, the whole object, to the right by a distance of x, and to
the top by a distance of y. A negative x or y value means it will move to the
left or the bottom, respectively.
- void rotate():
Rotate the object 90 degrees around its centre. Since all objects under
consideration are "symmetric", it makes no difference whether it is rotated
clockwise or anticlockwise.
For example, for a line segment with two endpoints (0,0) and (10,0), rotating
will change its endpoints to (5,5) and (5,-5); for a rectangle with four corners
(0,0), (10,0), (0,4) and (10,4), rotating will change the corners to (3,-3),
(7,-3), (3,7) and (7,7). Rotation has no effect (but is still a valid operation)
on Point or Circle.
- void scale(float f):
Scale up/down the size of the object by a factor f, relative to its centre. A
factor f > 1 indicates the object becomes bigger, and a factor 0 < f < 1
indicates the object becomes smaller. If f is zero or negative, throw a
std::invalid_argument exception, and do not change the object. "Relative
to its centre" means that the object's centre remains at the same position.
For example, if a rectangle with four corners (0,0), (0,10), (2,0) and (2,10)
is scaled up by a factor of 2, the corners become (-1,-5), (3,15), (3,-5) and
(-1,15). And a circle with centre (1,2) and radius 10, scaled by a factor f =
0.5, will still have centre (1,2) but the radius becomes 5. Scaling has no
effect (but is still a valid operation) on Point.
- bool contains(const Point& p):
Return true or false indicating whether the point p is "inside" the current
object (let's call it o here) or not. The depths of o and p are disregarded for
the purpose of this function. That is, even if o and p have different depths,
this function should return true if p is "inside" o as if they had the same
depth.
If this object o is a Point, the function returns true if and only if o and p have
the same x- and y-coordinates. If o is a line segment, it returns true if and
only if p lies between the two endpoints of o, including the two endpoints
themselves. If o is a rectangle or circle, it returns true if and only if p is on
the inside or the boundary of the rectangle/circle. Just to remind you, the
distance between two points (x1,y1) and (x2,y2) is given by the formula √(
(x1-x2)
2 + (y1-y2)
2 ).
- Destructor, copy constructor and copy assignment operator are assumed to
be not required (i.e. the default is adequate). If for some reason they are not
adequate for your implementation then you should supply them.

The figures below illustrates how rotate and scale work on a rectangle: (left) blue
rectangle rotates to become the orange one (and vice versa); (right) blue rectangle
scaled up with f=2 to become the orange one (or the orange one scaled down with
f=1/2 to become the blue one).

![image](https://user-images.githubusercontent.com/62874437/206722119-0e787f9f-8bb5-4616-9b86-86433f068eab.png)

### Other functions of Point
In addition to those inherited from the parent class, the Point class should support
the following operations:
- float getX(): return the x-coordinate of the point.
- float getY(): return the y-coordinate of the point.

### Other functions of LineSegment
In addition to those inherited from the parent class, the LineSegment class should
support the following operations:
- float getXmin(): return the x-coordinate of the left endpoint (or both
endpoints if the line is vertical).
- float getXmax(): return the x-coordinate of the right endpoint (or both
endpoints if the line is vertical).
- float getYmin(): return the y-coordinate of the bottom endpoint (or both
endpoints if the line is horizontal).
- float getYmax(): return the y-coordinate of the top endpoint (or both
endpoints if the line is horizontal).
- float length(): return the length of this line segment.

### Other functions of TwoDShape and its subclasses
In addition to those inherited from the parent class, all TwoDShape objects should
support the following operation:
- float area(): return the area of the object. (In case you need reminding,
for rectangles it is the width multiplied by the height, and for circle it is πr<sup>2</sup>
where r is the radius and the constant PI is defined in the Shape class.)

### Other functions of Rectangle
In addition to those inherited from the parent classes, the Rectangle class should
support the following operations:
- float getXmin(): return the x-coordinate of the left edge of the rectangle.
- float getXmax(): return the x-coordinate of the right edge of the rectangle.
- float getYmin(): return the y-coordinate of the bottom edge of the
rectangle.
- float getYmax(): return the y-coordinate of the top edge of the rectangle.

### Other functions of Circle
In addition to those inherited from the parent classes, the Circle class should
support the following operations:
- float getX(): return the x-coordinate of the centre.
- float getY(): return the y-coordinate of the centre.
- float getR(): return the radius.

### The Scene class
This class stores a collection of shared pointers to some Shape objects, so that the
objects can be "drawn" on the screen. It should support the following operations:
`void addObject(shared_ptr<Shape> p);`
Add the shared pointer p that points to some Shape (or its subclasses) object to
this Scene object. After the call, the pointer p (and the object that it points to) must
remain "intact", and both the caller of this function and this Scene object share the
"ownership" of the object being pointed to. In other words, any changes made to
one of them is reflected in the other. For example, in the following code:
`shared_ptr<Rectangle> rp = make_shared<Rectangle>(...);`
`Scene s;`
`s.addObject(rp);`
`rp->translate(1,2);`

- After the rectangle pointed to by rp is translated, the rectangle added to s is
translated as well.
- `void setDrawDepth(int d);`
Set the "drawing depth" to d, which means that when operator<< is called
(see the next bullet point), it draws all objects at depth d or less. For
example, if d=2, it draws all objects with depth 0, 1, 2, but not those with
depth 3, 4, 5, etc. If this function is never called, operator<< should draw all
objects of any depth.

`ostream& operator<<(ostream& out, const Scene& s);`
Overloaded output stream redirection operator, to be implemented as a friend
function (not a member function) of this class. It "draws" all objects to the screen,
as follows. There is a rectangular "drawing area" of size defined in the constants
WIDTH and HEIGHT in the Scene class. This function outputs to the stream a
number of lines equal to HEIGHT, where each line has exactly WIDTH characters.

These lines are joined by the newline ('\n') character, and the final line is followed
by a newline character as well. The j-th line from the **bottom**, and the i-th
character from the left in this line (count starts from 0), correspond to the point
with integer coordinates (i,j). That is, the rectangular area corresponds to the
coordinates from (0,0) in the bottom left, to (WIDTH-1, HEIGHT-1) in the top right.
Each character in the above lines is the character '*', if the corresponding integer
coordinates (i,j) is inside part of any object (as defined by the contains()
function) and that object has depth no more than the drawing depth (see previous
bullet point); otherwise it is the blank space ' ' character.
Effectively, all objects of different depths (that are at most the drawing depth) are
"overlayed" on top of each other. Also note that some objects may be partially or
wholly outside of the drawing area, and they (or those parts) are not drawn.
For example, with the default WIDTH and HEIGHT values of 20 and 60, a scene with
a point (0,0), a line segment with endpoints (0,19) and (59,19), a rectangle with
opposite corners (59,0) and (55,19), and a circle with centre (30,0) and radius 10,
all with depth 0, may be drawn like this if the drawing depth is also 0:

![image](https://user-images.githubusercontent.com/62874437/206820722-56ae95cd-01c0-4e12-a23b-5822703f817d.png)

- (yes, I know it doesn't look like a semi-circle...) Due to the floating point
nature of the coordinates, this function will have the interesting "feature"
that it only draws things with integer coordinates; for example a line
segment between (1,1) and (1,5) will be drawn, while one between (1.5, 1)
and (1.5, 5) will not.

In all places that require comparing floating point values, you can ignore the issue
of floating-point inaccuracies. That is, you can just compare two floats with x==y.
