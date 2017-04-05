#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>



int main()
{

int ds ;

ds = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP) ;

if( ds != -1 ) 
  printf(" Correspendance entre SOCK_STREAM ET IPPROTO_TCP \n");
else 
printf (" Pas de Correspendance entre SOCK_STREAM ET IPPROTO_TCP\n");


return 0;
}
