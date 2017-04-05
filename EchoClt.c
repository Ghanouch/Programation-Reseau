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
	
   int ds ;
   struct sockaddr_in adrSrv ;
   char *reqs , *reps ;

   reqs = malloc ( 1024 * sizeof(char));
     reps = malloc ( 1024 * sizeof(char));

   adrSrv.sin_family = PF_INET ; 
   adrSrv.sin_port = htons(99);
   inet_aton( "127.0.0.1" , &adrSrv.sin_addr ) ;
   memset ( &adrSrv.sin_zero , '0' , 8);


	ds = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP);

	if ( ds == -1 )
		 printf("Error Socket \n");	

	printf (" SOCKET ETABLI \n");
    
    connect( ds ,  (struct sockaddr *) &adrSrv , sizeof(struct sockaddr));

    printf (" Donnez votre Message : ");
    gets(reqs);
   
    printf("%s\n", reqs);

    send( ds , reqs , strlen(reqs) , 0);
     
    memset ( reps , '\0' , 1024);

    recv( ds , reps , 1024 , 0 );

         printf ("Le message recu est : %s \n",reps); 


    close(ds);


	return 0;
}