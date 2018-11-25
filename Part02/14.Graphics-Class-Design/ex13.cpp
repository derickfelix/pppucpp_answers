/*
    Modify Binary_tree to take a parameter (or parameters) to indicate
    what kind of line to use to connect the nodes (e.g., an arrow)
    pointing down or a red arrow pointing up). Note how this exercise
    and the last use two alternative ways of making a class hierarchy
    more flexible and useful
*/
#include "Custom_objects.h"

int main()
{
    Simple_window win(Point{250, 60}, win_width, win_height, "Exercise 12 - Chapter 14: Graphics Class Design");

    try
    {
        

        win.wait_for_button();
    }
    catch (const exception &e)
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