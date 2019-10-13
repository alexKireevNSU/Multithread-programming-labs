#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void* print_strings(void* args)
{
  // Печать переданной строки и текста сообщения в stdout
  int i;
  for (i = 0; i < 10; i++)
  {
    printf("%s %d TEXT\n", (char*)args, i);
  }
  // Выход из нити функцией pthread_exit
  pthread_exit(NULL);
}

int main()
{
  // Идентификатор нити
  pthread_t thread;

  // Строка передаваемая в качестве параметра для определения нити "a"
  char* name = "a";
  /*
      Создание нити с атрибутами по умолчанию и
    сохранение возвращаемого значения функции pthread_create.
      Возможные значения возвращаемого значения:
    0       - при успешном завершении
    EAGAIN  - нехватка ресурсов (память, лимит на кол-во нитей в процесе)
    EINVAL  - недопустимое значение одного из параметров
    EPERM   - недостаточно прав для исполнения нити с заданными атрибутами
  */
  int stat = pthread_create(&thread, NULL, print_strings, (void*)name);
  /*
    Проверка успешного выполнения функции pthread_create
  */
  if (stat != 0)
  {
    perror(NULL);
    return -1;
  }
  /*
      Ожидание завершения нити "b" с игнорированием кода возврата нити и
    сохранение возвращаемого значения функции pthread_join.
      Возможные значения возвращаемого значения:
    0       - при успешном завершении
    EDEADLK - при попытке нити ожидать саму себя
    EINVAL  - при попытке ожидания отсоединённой (detached) нити
    ESRCH   - невозможно найти нить с таким идентификатором

  */
  int err = pthread_join(thread, NULL);
  /*
    Проверка успешного выполнения функции pthread_join
  */
  if (err != 0)
  {
    perror(NULL);
    return -1;
  }
  // Строка передаваемая в качестве параметра для определения нити "b"
  name = "b";
  // Исполнение print_strings
  print_strings((void*)name);
  // Выход из главной нити функцией pthread_exit
  pthread_exit(NULL);
}
