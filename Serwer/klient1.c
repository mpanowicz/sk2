#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

void childend()
{
  wait(NULL);
  printf("Koniec połączenia\n");
}

int main(int argc, char** argv) 
{
  int fd, n , b,l,fd2,fd3,size, on=1;
  struct sockaddr_in sa;
  struct sockaddr_in sa2;
  struct sockaddr_in caddr[atoi(argv[1])];
  struct hostent* addrent;
  signal(SIGCHLD, childend);
  fd = socket(PF_INET, SOCK_STREAM, 0);
  fd3 = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
  sa.sin_family = PF_INET;
  sa.sin_port = htons(4576);
  sa.sin_addr.s_addr = INADDR_ANY;
  addrent=gethostbyname("localhost");
  sa2.sin_family = PF_INET;
  sa2.sin_port = htons(1234);
  memcpy(&sa2.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
  connect(fd3, (struct sockaddr*)&sa2, sizeof(sa2));
  int port=htons(4576);
  printf("%d\n", port);
  write(fd3, &port, sizeof(port));
  close(fd3);
  b=bind(fd, (struct sockaddr*)&sa, sizeof(sa));
  l=listen(fd,10);
  size=sizeof(caddr[0]);
  while(1)
  {
    fd2=accept(fd, (struct sockaddr*)&caddr[0], &size);
    if(!fork())
    {
      close(fd);
      printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
      close(fd2);
      return 0;
    }
    close(fd2);
  }
  close(fd);
  return 0;
}