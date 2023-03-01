#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int count = 0;
pthread_mutex_t lock;

void *counter(void *y)
{
  pthread_mutex_lock(&lock);
  
  long limit = (long)y;
  for (int i = 0; i < limit; i++){
    count++;
  }

  pthread_mutex_unlock(&lock);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int status, x;
  long y;
  long j;
  if(argc>2){
    x = atoi(argv[1]);
    y = (long)atoi(argv[2]);
  }else{
    x = 4;
    y = 10000;
  }
  pthread_t threads[x];
  if(pthread_mutex_init(&lock, NULL) != 0){
      printf("\n mutex init has failed\n");
      return 1;
  }
  
  for(j=0; j < x; j++){
    status = pthread_create(&threads[j], NULL, counter, (void *)y);
    
    if (status != 0){
      printf("Oops, pthread_create returned error code %d\n", status);
      exit(-1);
    }
  }
 printf("%u\n",count);
 for(int i = 0; i < x; i++){
   pthread_join(threads[i], NULL);
 }
 pthread_mutex_destroy(&lock);
}
