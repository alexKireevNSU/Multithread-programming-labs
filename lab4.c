#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void* print_func(void* args)
{
  while (1)
  {
    int err = write(0, "a", 1);
    if (err == -1)
    {
      perror("slave thread");
      pthread_exit(NULL);
    }
  }
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread;
  int stat;
  void* stat_addr;
  stat = pthread_create(&thread, NULL, print_func, NULL);
  if (stat != 0)
  {
    perror(NULL);
    return -1;
  }
  sleep(2);
  pthread_cancel(thread);
  stat = pthread_join(thread, &stat_addr);
  if (stat != 0)
  {
    perror(NULL);
    return -1;
  }
  if (stat_addr == PTHREAD_CANCELED)
    printf("\nmain(): thread canceled\n");
  pthread_exit(NULL);
}
