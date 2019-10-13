#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void cleanup_handler(void* arg)
{
  printf("thread cancelled\n");
}

void* print_func(void* args)
{
  pthread_cleanup_push(cleanup_handler, NULL);
  while (1)
  {
    int err = write(0, "a", 1);
    if (err == -1)
    {
      perror("slave thread");
      pthread_exit(NULL);
    }
  }
  pthread_cleanup_pop(0);
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
  pthread_exit(NULL);
}
