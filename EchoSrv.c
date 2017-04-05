#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[])
{

   int dss , dsc , i , lgclient ;
   struct sockaddr_in adrSrv , adrclt ;
   char *reqs , *reps ;

   reqs = malloc ( 1024 * sizeof(char));
     reps = malloc ( 1024 * sizeof(char));

   adrSrv.sin_family = PF_INET ; 
   adrSrv.sin_port = htons(99);
   inet_aton( "127.0.0.1" , &adrSrv.sin_addr ) ;
   memset ( &adrSrv.sin_zero , '0' , 8);



	dss = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP);
  
	if ( dss == -1 )
		 printf("Error Socket \n");	
	printf (" SOCKET ETABLI \n");

    if ( bind ( dss , ( struct sockaddr *) &adrSrv , sizeof(struct sockaddr ) ) == -1)
    	printf (" Error BIND \n");


    printf (" BIND ETABLI \n");

   listen ( dss , 5);

   printf (" LISTEN ETABLI \n");
    while (1)
    {


    printf("ATTENTE CLIENT \n");	
     
    dsc = accept ( dss , (struct sockaddr *) &adrclt , (socklen_t*) &lgclient );

    printf (" BIENVENUE CLIENT \n");
    memset( reps , '\0' , 1024 );
    memset( reqs , '\0' , 1024 );

    recv(dsc ,reqs , 1024 , 0) ;

    printf (" VOTRE MESSAGE : %s \n",reqs);
     
    

    for ( i = 0 ; i < strlen(reqs) ; i++ )
    	reps[i] = toupper(reqs[i]);
   
    send( dsc , reps , 1024 , 0 );

    close (dsc);
    }

    close (dss);
	return 0;
}
