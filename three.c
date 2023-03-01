#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int count = 0;
bool lock = false;

bool testandset(bool lock){
  bool new = lock;
  lock = true;
  return new;
}

void *counter(void *y)
{
  while (testandset(lock));
  
  long limit = (long)y;
  for (int i = 0; i < limit; i++){
    count++;
  }

  lock = false;
  return NULL;
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
    y = 10000;
    x = 4;
  }
  pthread_t threads[x];
  
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
}
