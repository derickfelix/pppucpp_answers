#include "Custom_shapes.h"

#include <cmath>

////////////////////////////////// Arc /////////////////////////////////////////
Arc::Arc(Point p, int ww, int hh, int eaa)
: w(ww), h(hh), ia(0), ea(eaa)
{
  add(Point{p.x-w, p.y-h});
}

Arc::Arc(Point p, int ww, int hh, int iaa, int eaa)
: w(ww), h(hh), ia(iaa), ea(eaa)
{
  add(Point{p.x-w, p.y-h});
}

Point Arc::center() const
{
  return Point{point(0).x+w, point(0).y+h};
}

void Arc::draw_lines() const
{
  if (color().visibility()) {
    fl_arc(point(0).x, point(0).y, w, h, ia, ea);
    fl_line(point(0).x, point(0).y+w/2, point(0).x, point(0).y+w+20);
  }
}

////////////////////////////////// Box /////////////////////////////////////////
Box::Box(Point p, int w, int h)
: width(w), height(h)
{
  if (w <= 0 || h <= 0)
    error("Bad box: non-positive side");

  add(p);
}

void Box::draw_lines() const
{
  if (color().visibility())
  {
    Point c1{point(0).x, point(0).y};
    Point c2{point(0).x + width, point(0).y};
    Point c3{point(0).x, point(0).y + height};
    Point c4{point(0).x + width, point(0).y + height};

    fl_arc(c1.x, c1.y, width, height, 90, 180);
    fl_arc(c2.x, c2.y, width, height, 0, 90);
    fl_arc(c3.x, c3.y, width, height, 180, 270);
    fl_arc(c4.x, c4.y, width, height, 270, 360);

    fl_line(c1.x+width/2, c1.y, c2.x+width/2, c2.y);
    fl_line(c2.x+width, c2.y+height/2, c4.x+width, c4.y+height/2);
    fl_line(c1.x, c1.y+height/2, c3.x, c3.y+height/2);
    fl_line(c3.x+width/2, c3.y+height, c4.x+width/2, c4.y+height);

  }
}

////////////////////////////////// Arrow ///////////////////////////////////////
Arrow::Arrow(Point p, int l, int a)
: length(l), angle(a)
{
  add(p);
}

void Arrow::draw_lines() const
{
  if (color().visibility())
  {
    Point init {point(0).x, point(0).y};

    Point other {
      int(length * cos(radian(angle))) + init.x,
      abs(int(length * sin(radian(angle))) - init.y)
    };
    Point arrow {
      int(10 * cos(radian(angle))) + other.x,
      abs(int(10 * sin(radian(angle))) - other.y)
    };
    Point arrowPlus90 {
      int(5 * cos(radian(angleAdd(angle, 90)))) + other.x,
      abs(int(5 * sin(radian(angleAdd(angle, 90)))) - other.y)
    };
    Point arrowMinus90 {
      int(5 * cos(radian(angleSub(angle, 90)))) + other.x,
      abs(int(5 * sin(radian(angleSub(angle, 90)))) - other.y)
    };    

    fl_line(init.x, init.y, other.x, other.y);
    fl_line(other.x, other.y, arrowPlus90.x, arrowPlus90.y);
    fl_line(other.x, other.y, arrowMinus90.x, arrowMinus90.y);
    fl_line(arrowPlus90.x, arrowPlus90.y, arrow.x, arrow.y);
    fl_line(arrowMinus90.x, arrowMinus90.y, arrow.x, arrow.y);

  }
}
