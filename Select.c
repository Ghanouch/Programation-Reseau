#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/select.h>
#include <string.h>

int main(int argc, char const *argv[])
{

   int dss , dsc , nbrClient = 0, maxDesc , i , j;
   struct sockaddr_in adrSrv , adrclt ;
   int lstSocket[20];
   socklen_t lgrClient = sizeof(adrclt);
   char *reps ;
   fd_set ensembleDS ;

    reps = malloc ( 1024 * sizeof(char));

   adrSrv.sin_family = PF_INET ; 
   adrSrv.sin_port = htons(5000);
   inet_aton( "127.0.0.1" , &adrSrv.sin_addr ) ;
   memset ( &adrSrv.sin_zero , '0' , 8);



	 dss = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP);
  
	  if ( dss == -1 )
		                 printf("Error Socket \n");	
	

    if ( bind ( dss , ( struct sockaddr *) &adrSrv , sizeof(struct sockaddr ) ) == -1)
    	                     printf (" Error BIND \n");

   listen ( dss , 20);

   lstSocket[0] = dss ;
   nbrClient++ ;
   maxDesc = dss ;

   while(1)
   {

    FD_ZERO(&ensembleDS);
  
    for (i = 0 ; i < nbrClient ; i++ ) {   // Ici la 1ére fois , on ajoute le Server
      FD_SET(lstSocket[i] , &ensembleDS);
      maxDesc = lstSocket[i] > maxDesc ? lstSocket[i] : maxDesc ;
    }
    

    select(maxDesc , &ensembleDS , NULL , NULL , NULL);
    if(FD_ISSET(dss , &ensembleDS)) // Ici qlq solicite le serveur , il demande la connextion ;
    {
      dsc = accept ( dss , (struct sockaddr *) &adrclt , (socklen_t*) &lgrClient );
      printf("le client ayant le descripteur %d vient de se connecter !!!! \n", dsc);
      //maxDesc = dsc > maxDesc ? dsc : maxDesc ;
      FD_SET(dsc , &ensembleDS);
      lstSocket[nbrClient] = dsc ;
      nbrClient++ ;

    }

    else
    {  // Ici un client veut se déconnecter ou un msg qui arrive , c est un client qui est solicité

      for ( i = 0 ; i < nbrClient ; i++)
      {

        if(FD_ISSET(lstSocket[i] , &ensembleDS))
        {
          if(recv(lstSocket[i]  , reps , strlen(reps) , 0) <= 0 )
          {
             close(lstSocket[i]);
             printf("le client ayant le descripeteur %d s est deconnecte !!!!!!!\n", lstSocket[i]);
             for ( j=i ; j < nbrClient ; j++)  lstSocket[j] = lstSocket[j+1]; 
             nbrClient -- ;
          }

        }
      }



    }
 

   }


   return 0;
}
