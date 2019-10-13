#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define num_steps 200000000

typedef struct thread_arg
{
  int start;
  int finish;
  double result;
}thread_arg;

thread_arg init_thread_arg(int start, int finish)
{
  thread_arg r;
  r.start = start;
  r.finish = finish;
  r.result = 0.0;
  return r;
}

void* calc_part_sum(void* args)
{
  thread_arg* arg = (thread_arg*)args;

  int i;
  for (i = (*arg).start; i < (*arg).finish; i++)
  {
    (*arg).result += 1.0 / (i*4.0 + 1.0);
    (*arg).result -= 1.0 / (i*4.0 + 3.0);
  }

  pthread_exit(NULL);
}

int main(int argc, char** argv)
{
  int num_of_threads = atoi(argv[1]);
  if (num_of_threads <= 0)
  {
    printf("Wrong thread number\n");
    return (EXIT_FAILURE);
  }
  pthread_t threads[num_of_threads];

  thread_arg part_sums[num_of_threads];
  int thread_num_steps = num_steps / num_of_threads;
  int i = 0;
  for (i = 0; i < num_of_threads - 1 + (num_of_threads == 1); i++)
    part_sums[i] = init_thread_arg(i*thread_num_steps, (i + 1)*thread_num_steps);
  if (num_of_threads != 1)
    part_sums[num_of_threads - 1] = init_thread_arg((num_of_threads - 1)*thread_num_steps, (num_of_threads - 1)*thread_num_steps + num_steps % num_of_threads);


  for (i = 0; i < num_of_threads; i++)
  {
    int stat;
    stat = pthread_create(&(threads[i]), NULL, calc_part_sum, (void*) &(part_sums[i]));
    if (stat != 0)
    {
      perror(NULL);
      return -1;
    }
  }

  for (i = 0; i < num_of_threads; i++)
  {
    int err = pthread_join(threads[i], NULL);
    if (err != 0)
    {
      perror(NULL);
    }
  }

  double result = 0.0;
  for (i = 0; i < num_of_threads; i++)
    result += part_sums[i].result;
  result *= 4.0;

  printf("Result: %lf\n", result);

  return (EXIT_SUCCESS);
}
