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
    int fd, n , b,l,fd2,size, on=1,i=0;
    struct sockaddr_in sa;
    struct sockaddr_in caddr[atoi(argv[1])];
    signal(SIGCHLD, childend);
    fd = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    sa.sin_family = PF_INET;
    sa.sin_port = htons(1234);
    sa.sin_addr.s_addr = INADDR_ANY;
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
	    read(fd2,&caddr[0].sin_port, 4);
	    printf("Nowy port: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
		printf("Nowy port: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
		printf("Nowy port: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
		printf("Nowy port: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
	    float matrixA[2][2] = {{2, 2},{2, 2}};
	    float matrixB[2][2] = {{2, 2},{2, 2}};
	    int rowsCount = sizeof(matrixA)/sizeof(matrixA[0]);
	    int len = sizeof(matrixA[0])/sizeof(float);
	    printf("Rows:%d Columns:%d\n", rowsCount, len);
	    writeI(fd2, &len);
	    writeI(fd2, &rowsCount);
	    int i, j;
	    for(i = 0; i < rowsCount; i++)
	    {
		for(j = 0; j < len; j++)
		{
		    writeI(fd2, &i);
		    writeI(fd2, &j);
		    write(fd2, matrixA[i], sizeof(matrixA[0]));
		    write(fd2, matrixB[j], sizeof(matrixB[0]));
		    float result;
		    int x, y;
		    readI(fd2, &x);
		    readI(fd2, &y);
		    readF(fd2, &result);
		    printf("Row:%d Column:%d Value:%f\n", x, y, result);
		}
	    }
	    write(fd2, "\n", 1);
	    close(fd2);
	    return 0;
	}
	close(fd2);
    }
    close(fd);
    return 0;
}