#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	
     struct sockaddr_in adrSrv ;
     int i , ds ;

     adrSrv.sin_family = AF_INET ;
     inet_aton("127.0.0.1", &adrSrv.sin_addr );
     memset(&adrSrv.sin_zero, '0' , 8 ) ;

     ds = socket ( AF_INET , SOCK_STREAM , 6);

     if(ds == -1) printf("SOCKET ERREUR \n");

     for ( i = 1 ; i < 65535 ; i++)
     {
      
      adrSrv.sin_port = htons(i);
      ds = socket ( AF_INET , SOCK_STREAM , 6);
      if ( connect ( ds , (struct sockaddr *) & adrSrv , sizeof( struct sockaddr) ) != -1  )
      	  printf ( "TCP PORT %d est ouvert \n",i);


     }

     // TEST PORT UDP 


     ds = socket ( AF_INET , SOCK_DTGRAM , 17);

     if(ds == -1) printf("SOCKET ERREUR \n");

     for ( i = 1 ; i < 65535 ; i++)
     {
      
      adrSrv.sin_port = htons(i);
      ds = socket ( AF_INET , SOCK_DTGRAM , 17);
      if ( connect ( ds , (struct sockaddr *) & adrSrv , sizeof( struct sockaddr) ) != -1  )
          printf ( "UDP PORT %d est ouvert \n",i);


     }


    close(ds);


	return 0;
}