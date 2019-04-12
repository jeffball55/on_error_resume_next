#include <stdio.h>

void segfault()                                                                                                                                                                                                                  
{
  int *foo = NULL;                                                                                                                                                                                                               
  *foo = 1; //causes a segfault                                                                                                                                                                                                  
  foo += 0xdeadbeef;                                                                                                                                                                                                             
  return;                                                                                                                                                                                                                        
}

int main()
{
  segfault();                                                                                                                                                                                                                    
  printf("Successfully resumed after segfault\n");                                                                                                                                                                                          
  return 0;                                                                                                                                                                                                                      
}
