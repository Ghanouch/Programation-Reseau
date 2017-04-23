#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>


int compare( char* str1 , char* str2 )
{
	int i;

 if ( strlen(str1) != strlen(str2 ) ) return -1 ;
 
 for ( i = 0 ; i < strlen(str1) ; i++ )
 {
 	if ( str1[i] != str2[i]) 
 		return -1 ;
 }
 return 0 ;

}
int main(int argc, char const *argv[])
{
	 
	 int dss , dsc , lgtClt , exit  , i =0 ;
	 char *reqs , *reps ;
	 struct sockaddr_in adrSrv , adrClt ;

     reqs = malloc ( 1024 * sizeof(char));
     reps = malloc ( 1024 * sizeof(char));

     adrSrv.sin_family = AF_INET ;
     adrSrv.sin_port = htons (208);
     inet_aton ("127.0.0.1" , & (adrSrv.sin_addr) );
     memset( &(adrSrv.sin_zero), '0' , 8 );

     dss = socket ( PF_INET , SOCK_STREAM , IPPROTO_TCP );

     if ( dss == -1 )
     	printf("Socket Error\n");


    if ( bind ( dss , (struct sockaddr *) & adrSrv , sizeof ( struct sockaddr ) )  == -1 )
    	printf (" Error BIND \n");


    listen( dss , 10 );

    time_t laDate ;
	time(&laDate);
	struct tm Fdate = *localtime(&laDate);


    while ( 1 )
    {
     
     exit = 0 ;
     
     dsc = accept( dss , (struct sockaddr *) &adrClt , (socklen_t*) &lgtClt );
     
     printf("CLIENT BIENVENUE\n");
     while ( exit == 0 )
     {
      recv ( dsc , reqs , 1024 , 0 );

    	printf ( " RECU : %s " , reqs);

       if( compare(reqs,"HEURE") == 0 )
        	sprintf(reps,"%d",Fdate.tm_hour);

       if( compare(reqs,"DATE") == 0 )
       	 strcpy(reps , asctime(&Fdate));
 	
 	 	if( compare(reqs,"EXIT") == 0 )
       	  exit = 1 ;
       	time(&laDate);
      Fdate = *localtime(&laDate);
      strcpy(reps , asctime(&Fdate));
      //printf("%d A ENVOYER ----->  %s  \n", i++ ,reps);
      send( dsc , reps , strlen(reps) , 0);
      
      memset(reqs,'\0', 1024); 	
      memset(reps,'\0', 1024); 	

     }

     close ( dsc );



    }
    close (dss);
	return 0;
}