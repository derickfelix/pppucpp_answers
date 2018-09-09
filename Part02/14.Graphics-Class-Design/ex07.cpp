/*
    Define a Striped_closed_polyline using the technique from Striped_rectangle
    (this requires some algorithmic inventiveness).
*/
#include "Custom_objects.h"

int main()
{
  Simple_window win(Point{250, 50}, win_width, win_height, "Exercise 06 - Chapter 14: Graphics Class Design");

  try
  {
    Striped_closed_polyline scp(2);
    scp.add({100, 200});
    scp.add({200, 200});
    scp.add({100, 150});
    scp.add({150, 100});
    scp.add({300, 150});

    win.attach(scp);
    win.wait_for_button();
  }
  catch (const exception& e)
  {
    Text em(Point{150, 200}, "Exception caught: ");
    Text emd(Point{280, 200}, e.what());
    win.attach(em);
    win.attach(emd);
    win.wait_for_button();
  }
  catch (...)
  {
    Text em(Point{150, 200}, "Unknown exception caught!");
    win.attach(em);
    win.wait_for_button();
  }

  return 0;
}
