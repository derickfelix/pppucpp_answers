/*
  Write a program called multi_input.cpp  that prompts the user to enter several
  integers in any combination of octal, decimal, or hexadecimal, using the 0 and
  0x base  suffixes;  interprets the  number  correctly;  and  converts  them to
  decimal form. Then your  program  should  output the values in prorpely spaced
  columns like this:
        0x43  hexadecimal   converts to 67  decimal
        0123  octal         converts to 83  decimal
          65  decimal       converts to 65  decimal
*/
#include "std_lib_facilities.h"

int main()
{
  vector<string> integers;
  cout << "Enter some integers, it can be in decimal (no prefix), octal (0 prefix) or hexadecimal (0x prefix)\n";
  cout << "Type '|' to stop: ";
  int larger_w = 0;
  for (string number; cin >> number; ) {
    if (number == "|") break;
    if (larger_w < number.size()) larger_w = number.size();
    integers.push_back(number);
  }

  for (string& integer : integers) {
    cout << setw(larger_w) << integer << '\t';
    istringstream iss {integer};
    int number = 0;
    if (integer.size() > 2 && integer[0] == '0' && integer[1] == 'x') {
      iss >> hex >> number;
      cout << "hexadecimal\t";
    } else if (integer.size() > 1 && integer[0] == '0') {
      cout << "octal\t\t";
      iss >> oct >> number;
    } else {
      cout << "decimal\t\t";
      iss >> number;
    }
    cout << "converts to " << number << "\tdecimal\n";
  }


  return 0;
}
