//
// Solution for ACM-ICPC 5740 - Citizenship Application
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5740 5740.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Find the first day a Person can apply for
//               Citizenship in Canada
//

#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype>

using namespace std;
using namespace std::rel_ops;

/* Howard Cheng's Date Class */
struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1980;
  
  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1980, int mon = 1, int day = 1)
  {
    yyyy = yr;
    mm = mon;
    dd = day;
  }
   
  // comparison operators
  bool operator==(const Date &d) const
  { return dd == d.dd && mm == d.mm && yyyy == d.yyyy; }

  bool operator<(const Date &d) const
  { return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
      (yyyy == d.yyyy && mm == d.mm && dd < d.dd); }

  // Returns true if yr is a leap year
  static bool leapYear(int y)
  { return (y % 400 ==0 || (y % 4 == 0 && y % 100 != 0)); }

  // number of days in this month
  static int daysIn(int m, int y)
  {
    switch (m) {
    case 4  :
    case 6  :
    case 9  :
    case 11 :
      return 30;
    case 2  :
      if (leapYear(y)) {
	return 29;
      }
      else {
	return 28;
      }
    default :
      return 31;
    }
  }
   
  // add n days to the date: complexity is about n/30 iterations
  void addDay(int n = 1)
  {
    dd += n;
    while (dd > daysIn(mm,yyyy)) {
      dd -= daysIn(mm,yyyy);
      if (++mm > 12) {
	mm = 1;
	yyyy++;
      }
    }
    
    while (dd < 1) {
      if (--mm < 1) {
	mm = 12;
	yyyy--;
      }
      dd += daysIn(mm,yyyy); 
    }
  }

   
  // add n months to the date: complexity is about n/12 iterations
  void addMonth(int n = 1)
  {
    mm += n;
    while (mm > 12) {
      mm -= 12;
      yyyy++;
    }
    
    while (mm < 1)  {
      mm += 12;
      yyyy--;
    }
    
    if (dd > daysIn(mm,yyyy)) {
      dd = daysIn(mm,yyyy);
    }
  }

  // add n years to the date
  void addYear(int n = 1)
  {
    yyyy += n;
    if (!leapYear(yyyy) && mm == 2 && dd == 29) {
      dd = 28;
    }
  }
   
   
  // number of days since 1980/01/01, including the current date
  int daysFromStart() const
  {
    int c = 0;
    Date d(BASE_YEAR, 1, 1);
    Date d2(d);

    d2.addYear(1);
    while (d2 < *this) {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
    }

    d2 = d;
    d2.addMonth(1);
    while (d2 < *this) {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
    }
    while (d <= *this) {
      d.addDay();
      c++;
    }
    return c;
  }
};

// Reads a date in mm/dd/yyyy format, assumes date is valid and in the
// right format
istream& operator>>(istream &is, Date &d)
{
  char c;
  return is >> d.mm >> c >> d.dd >> c >> d.yyyy;
}

// print date in mm/dd/yyyy format
ostream& operator<< (ostream &os, const Date &d) {
  char t = os.fill('0');
  os << d.mm << '/' << d.dd<< '/' << setw(2) << d.yyyy;
  os.fill(t);
  return os;
}

const int MAXDAYS = 20000;

int main()
{
   // setup
   Date start, end;
   int vacay;
   
   while(cin >> start >> end >> vacay)
   {
      // start looking at the first
      // date of residence in Canada
      Date CitizenApp = start;
      int vtrips[MAXDAYS];
      int time = 0, startTime = start.daysFromStart(),
	 endTime = end.daysFromStart() - startTime;

      // days before the landing date should
      // be counted as half days (normalized as 1)
      fill(vtrips, vtrips+(endTime), 1);

      // days after the landing date should
      // be ocunted as full days (normalized as 2)
      fill(vtrips+(endTime), vtrips+MAXDAYS, 2);      

      // build vacation array;
      for(int i = 0; i < vacay; i++)
      {
	 Date vstart, vend;
	 cin >> vstart >> vend;

	 // no matter where these days are,
	 // fill between them with 0 since
	 // days spent outside the country
	 // do not count towards days stayed
	 fill(vtrips + (vstart.daysFromStart() - startTime),    
	      vtrips + (vend.daysFromStart() - startTime + 1), 0);
      }

      // length counts the total days
      // we have included in our time
      // in canada
      int length = 0;

      // add days until the time spent
      // in Canada is equal to 1095 (*2 for normalizing)
      for(int i = 0; time < 2*1095; i++)
      {
	 CitizenApp.addDay();

	 // if we are looking at less than
	 // 1460 days, just add the next day
	 if(length < 1460)
	 {
	    time += vtrips[i];
	    length++;
	 }

	 // if we are looking 1460 days,
	 // we need to slide our "window"
	 // of days over
	 else
	 {
	    // remove the last one
	    time -= vtrips[i-length];

	    // add the new one
	    time += vtrips[i];
	 }
      }    

      // output
      cout << CitizenApp << endl;
   }
}
