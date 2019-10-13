#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void* print_strings(void* args)
{
  // ������ ���������� ������ � ������ ��������� � stdout
  int i;
  for (i = 0; i < 10; i++)
  {
    printf("%s %d TEXT\n", (char*)args, i);
  }
  // ����� �� ���� �������� pthread_exit
  pthread_exit(NULL);
}

int main()
{
  // ������������� ����
  pthread_t thread;

  // ������ ������������ � �������� ��������� ��� ����������� ���� "a"
  char* name = "a";
  /*
      �������� ���� � ���������� �� ��������� �
    ���������� ������������� �������� ������� pthread_create.
      ��������� �������� ������������� ��������:
    0       - ��� �������� ����������
    EAGAIN  - �������� �������� (������, ����� �� ���-�� ����� � �������)
    EINVAL  - ������������ �������� ������ �� ����������
    EPERM   - ������������ ���� ��� ���������� ���� � ��������� ����������
  */
  int stat = pthread_create(&thread, NULL, print_strings, (void*)name);
  /*
    �������� ��������� ���������� ������� pthread_create
  */
  if (stat != 0)
  {
    perror(NULL);
    return -1;
  }
  /*
      �������� ���������� ���� "b" � �������������� ���� �������� ���� �
    ���������� ������������� �������� ������� pthread_join.
      ��������� �������� ������������� ��������:
    0       - ��� �������� ����������
    EDEADLK - ��� ������� ���� ������� ���� ����
    EINVAL  - ��� ������� �������� ������������ (detached) ����
    ESRCH   - ���������� ����� ���� � ����� ���������������

  */
  int err = pthread_join(thread, NULL);
  /*
    �������� ��������� ���������� ������� pthread_join
  */
  if (err != 0)
  {
    perror(NULL);
    return -1;
  }
  // ������ ������������ � �������� ��������� ��� ����������� ���� "b"
  name = "b";
  // ���������� print_strings
  print_strings((void*)name);
  // ����� �� ������� ���� �������� pthread_exit
  pthread_exit(NULL);
}
