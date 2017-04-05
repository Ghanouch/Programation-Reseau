#include <time.h>


int main()
{

time_t laDate ;
time(&laDate);

struct tm Fdate = *localtime(&laDate);

printf ( " On est dans %d / %d / %d \n ",Fdate.tm_mday , Fdate.tm_mon+1 , Fdate.tm_year + 1900 );

printf (" date : %s \n ",asctime(&Fdate));


return 0 ;
}
