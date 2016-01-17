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
    int fd, n , b,l,fd2,size, on=1,i=0, con,petla=1;
    struct sockaddr_in sa;
    struct sockaddr_in caddr[100];
    int tab[100]={0};
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
	fd2=accept(fd, (struct sockaddr*)&caddr[i], &size);
	if(!fork())
	{
	    tab[i]=1;
	    int port,fd3, numer=i;
	    i++;
	    close(fd);
	    printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)caddr[numer].sin_addr), caddr[numer].sin_port);
	    read(fd2, &port, 4);
	    caddr[numer].sin_port=port;
	    //caddr[i].sin_port = htons(13240);
	    caddr[numer].sin_family=PF_INET;
	    printf("Nowy port: %s:%i\n", inet_ntoa((struct in_addr)caddr[numer].sin_addr), caddr[numer].sin_port);
	    close(fd2);
	    fd3 = socket(PF_INET, SOCK_STREAM, 0);
	    while(petla==1)
	    {
	    con=connect(fd3, (struct sockaddr*)&caddr[numer], sizeof(caddr[numer]));
	    if(con==-1)
	    {
	      printf("Serwer nie odpowiada\n");
	      sleep(5);
	    //licznik=licznik+1;
	    }
	    else 
	    {
	    petla=0;
	      
	    }
	  }
	    float matrixA[2][2] = {{2, 2},{2, 2}};
	    float matrixB[2][2] = {{2, 2},{2, 2}};
	    int rowsCount = sizeof(matrixA)/sizeof(matrixA[0]);
	    int len = sizeof(matrixA[0])/sizeof(float);
	    printf("Rows:%d Columns:%d\n", rowsCount, len);
	    writeI(fd3, &len);
	    writeI(fd3, &rowsCount);
	    int i, j;
	    for(i = 0; i < rowsCount; i++)
	    {
		for(j = 0; j < len; j++)
		{
		    writeI(fd3, &i);
		    writeI(fd3, &j);
		    write(fd3, matrixA[i], sizeof(matrixA[0]));
		    write(fd3, matrixB[j], sizeof(matrixB[0]));
		    float result;
		    int x, y;
		    readI(fd3, &x);
		    readI(fd3, &y);
		    readF(fd3, &result);
		    printf("Row:%d Column:%d Value:%f\n", x, y, result);
		}
	    }
	    write(fd3, "\n", 1);
	    close(fd3);
	    return 0;
	}
	close(fd2);
    }
    close(fd);
    return 0;
}