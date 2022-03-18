#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>


fd_set readfds; // create an FD set



int keypressed()
{
struct timeval timeout;
int retval;

  timeout.tv_sec=0;
  timeout.tv_usec=0;

  FD_ZERO(&readfds); // clear the set
  FD_SET(0,&readfds); // add stdin (fd 0) to set

  retval = select(1,&readfds,NULL,NULL,&timeout);
  if(retval == -1) {
    std::cout << "keypressed" << std::endl;
  }
  else if(retval) return 1;
  return 0;
} /* keypressed */

// int main()
// {
// char nextchar='@';

//   while(nextchar != 'q')
//   {
//     printf(".\n");
//     if(keypressed())
//     {
//       nextchar = getchar(); // clear input buffer
//       printf("KEY '%c'\n",nextchar);
//     }
//     usleep(100000);
//   }

//   return 0;
// }


