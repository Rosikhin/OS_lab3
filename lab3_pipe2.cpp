// 9893, Росихин Александр, 
// Дисциплина ОС,
// Лабораторная работа №3.

/*
 pipe2()
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>


int flag1 = 0;
int flag2 = 0;
int filedes[2];


void* thread1(void* flag1)
{
  char buffer;
  
  while (*((int*)flag1)==0 )
  {
  	buffer = 97 +rand() % 25;
  	write(filedes[1], &buffer, 1);
  	
  	usleep(1000);
  }
  return 0;
}


void* thread2(void* flag2)
{
  char buffer;
  
  while (*((int*)flag2)==0 )
  {
  	buffer = 0;
  	read(filedes[0], &buffer, 1);
  	std::cout << buffer;
  	
  	usleep(1000);
  }
  return 0;
}




int main()
{
 std::cout << "Росихин, 9893, ОС, Лаба 3.\n";
 pthread_t id1;
 pthread_t id2;

 
 pipe2(filedes, O_NONBLOCK);
  
 pthread_create(&id1, NULL, thread1, &flag1);
 pthread_create(&id2, NULL, thread2, &flag2); 

 std::cout << "Ждем нажатия\n";
  getchar();
 
  flag1 = 1;
  flag2 = 1;
  
  pthread_join(id1, NULL); 
  pthread_join(id2, NULL); 

  close(filedes[0]);
  close(filedes[1]);
  
  std::cout << "\nЗавершение работы программы.\n";
 


}
