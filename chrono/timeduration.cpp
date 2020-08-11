#include <iostream>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  typedef duration<int,std::ratio<60*60*24>> days_type;
  time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());

  std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

  return 0;
}
