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
     int ds ;
     char* reqs , *reps ;

     reqs = malloc ( 1024 * sizeof(char));
     reps = malloc ( 1024 * sizeof(char));

     adrSrv.sin_family = AF_INET ;
     adrSrv.sin_port = htons(80);
     inet_aton("127.0.0.1", &adrSrv.sin_addr );
     memset(&adrSrv.sin_zero, '0' , 8 ) ;

     ds = socket ( AF_INET , SOCK_STREAM , 6);

     if(ds == -1) printf("SOCKET ERREUR \n");
     
     if ( connect ( ds , (struct sockaddr *) & adrSrv , sizeof( struct sockaddr) ) == -1  ) 
     	printf (" SERVEUR INACTIF ");

        strcpy(reqs , "GET / \n");

        send (ds , reqs , 1024 , 0 );
        

        while ( recv ( ds , reps , 1024 , 0 ) > 0 )
        {
        	printf("%s\n", reps);
        	
        }


        close(ds);

      

	return 0;
}
