#include <stdio.h>
#include <string.h>
#include <time.h>

#include "com.h"

int main()
{
  double t;
  database data;
  t = clock();	
 data.read_database_from_file ("a1000000.txt");
//data.create();
  data.command (); 
  t = (clock() - t)/CLOCKS_PER_SEC;
 // data.print_database ();
  printf("\ntime = %lf\n", t);

  return 0;
}
