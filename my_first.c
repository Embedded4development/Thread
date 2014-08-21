#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/times.h>
#include<stdbool.h>





int data[10],dosignal=0;
int nval=0,ndata=0;
bool ready;
pthread_mutex_t mutex;
pthread_cond_t cond;


void* producer()
{
   for(;;)
    {
 	 pthread_mutex_lock(&mutex); //Lock Applied
 	 if(nval > 10)
          {
  	      printf("Buffer is full\n");
              pthread_mutex_unlock(&mutex); //Lock Released
              return 0;  
     	   }
        data[nval]=ndata;
        nval++;
        ndata++;
         ready++;
//         if(ready == 1)
           dosignal =1;
  
      pthread_mutex_unlock(&mutex); //Lock Released

   if(dosignal == 1)
      pthread_cond_signal(&cond);
sleep(1);
     }

}
void* consumer()
{
	for(;;)
	 {
	   pthread_mutex_lock(&mutex);
    	     while(ready ==0)
                pthread_cond_wait(&cond,&mutex);
                           
                 printf("value[%d] = %d\n",nval,ndata);
                 ready--;  
          	

         if(nval >10)
          {
            return 0;
            pthread_mutex_unlock(&mutex);
           }

            pthread_mutex_unlock(&mutex);
          }
 }

int main(void)
{

pthread_t prod,cons;

pthread_create(&prod,NULL,&producer,NULL);
printf("producer generated\n");
sleep(1);
pthread_create(&cons,NULL,&consumer,NULL);


pthread_join(prod,NULL);
pthread_join(cons,NULL);

return 0;
 }
