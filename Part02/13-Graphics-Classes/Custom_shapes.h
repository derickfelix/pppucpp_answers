#ifndef __Custom__Shapes__
#define __Custom__Shapes__

#include "Simple_window.h"
#include "Graph.h"

constexpr int win_width = 800;
constexpr int win_height = 600;

////////////////////////////////// Arc /////////////////////////////////////////
struct Arc : Shape
{
  Arc(Point p, int ww, int hh, int eaa); // center, width, height, end ang
  Arc(Point p, int ww, int hh, int iaa, int eaa); // center, width, height, init ang, end ang

  void draw_lines() const;

  Point center() const;
  Point focus1() const;
  Point focus2() const;

  void set_major(int ww)
  {
    set_point(0, Point{center().x-ww, center().y-h});
    w = ww;
  }

  void set_minor(int hh)
  {
    set_point(0, Point{center().x-w, center().y-hh});
    h = hh;
  }

  int major() const { return w; }
  int minor() const { return h; }
private:
  int w;
  int h;
  int ia;
  int ea;
};

////////////////////////////////// Box /////////////////////////////////////////
struct Box : Shape
{
  Box(Point p, int w, int h);

  void draw_lines() const;
  int w() const { return width; }
  int h() const { return height; }
private:
  int width;
  int height;
};

////////////////////////////////// Arrow ///////////////////////////////////////
constexpr double pi = 3.14159265359;
constexpr int angcirc = 360;

inline double radian(int angle)
{
  return angle * pi / 180;
}

inline double angleAdd(double a, double b)
{
  double angle = a + b;
  if (angle > angcirc) angle -= angcirc;
  return angle;
}
inline double angleSub(double a, double b)
{
  double angle = a - b;
  if (angle < 0) angle += angcirc;
  return angle;
}

struct Arrow : Shape
{
  Arrow(Point p1, int l, int a);
  void draw_lines() const;
private:
  int length;
  int angle;
};

/////////////////////////// Connection Points //////////////////////////////////
namespace cp {
  Point n(const Rectangle& r);
  Point s(const Rectangle& r);
  Point e(const Rectangle& r);
  Point w(const Rectangle& r);
  Point center(const Rectangle& r);
  Point ne(const Rectangle& r);
  Point se(const Rectangle& r);
  Point sw(const Rectangle& r);
  Point nw(const Rectangle& r);

  Point n(const Circle& c);
  Point s(const Circle& c);
  Point e(const Circle& c);
  Point w(const Circle& c);
  Point center(const Circle& c);
  Point ne(const Circle& c);
  Point se(const Circle& c);
  Point sw(const Circle& c);
  Point nw(const Circle& c);

  Point n(const Ellipse& e);
  Point s(const Ellipse& e);
  Point e(const Ellipse& e);
  Point w(const Ellipse& e);
  Point center(const Ellipse& e);
  Point ne(const Ellipse& e);
  Point se(const Ellipse& e);
  Point sw(const Ellipse& e);
  Point nw(const Ellipse& e);
}
///////////////////////////// Box_with_label ///////////////////////////////////
struct Box_with_label : Box
{
  Box_with_label(Point p, const string& s);

  void draw_lines() const;
private:
  string str;
};

//////////////////////////// Regular_hexagon ///////////////////////////////////

struct Regular_hexagon : Polygon
{
  Regular_hexagon(Point cc, int dd);

  Point center() const { return c; }
  int distance() const { return d; }
private:
  Point c;
  int d;
};

//////////////////////////// Regular_polygon ///////////////////////////////////

struct Regular_polygon : Polygon
{
  Regular_polygon(Point c, int s, int d);

  int getSides() const { return sides; }
  int getDistance() const { return distance; }
private:
  Point center;
  int sides;
  int distance;
};

//////////////////////////// Super_Ellipse /////////////////////////////////////

struct Super_Ellipse : Open_polyline
{
    Super_Ellipse(Point p, int ww, int hh);

    int sign(double w);
    int width() const { return w; }
    int height() const { return h; }
private:
  int w;
  int h;
};

//////////////////////////// Right_triangle ////////////////////////////////////
struct Right_triangle : Polygon
{
  Right_triangle(Point p, int ssa, int ssb, int ang);

  int size_a() const { return sa; }
  int size_b() const { return sb; }
  int angle() const { return a; }
private:
  int sa;
  int sb;
  int a;
};

////////////////////////////////// Poly ////////////////////////////////////////

struct Poly : Polygon
{
  Poly(initializer_list<Point> ps) { for (Point p : ps) add(p); }
};

///////////////////////////////// Start ////////////////////////////////////////

struct Star : Polygon
{

  Star(Point c, int pp, int ss);
  int points() const { return p; }
  int size() const { return s; }
private:
  int p;
  int s;
};

#endif // defined(__Custom__Shapes__)
