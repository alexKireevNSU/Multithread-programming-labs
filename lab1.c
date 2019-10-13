#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void* print_strings(void* args)
{
  int i;
  for (i = 0; i < 10; i++)
  {
    printf("%s %d TEXT\n", (char*)args, i);
  }
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread;
  int stat;
  char* name = "a";
  stat = pthread_create(&thread, NULL, print_strings, (void*)name);
  if (stat != 0)
  {
    perror(NULL);
    return -1;
  }
  char* name2 = "b";
  print_strings((void*)name2);
  pthread_exit(NULL);
}
