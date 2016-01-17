#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

#define MAX_SIZE 256
#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

void childend()
{
  wait(NULL);
  printf("Koniec połączenia\n");
}

float* readRow(int fd, int len)
{
    static float *row = NULL;
    row = (float *)calloc( len , sizeof(calloc) );
    read(fd, row, sizeof(float) * len);
    if (row == NULL)
    {
	printf("Error");
    }
    return row;
}


float multiply(float* row, float* column, int len)
{
    float result;
    result = 0;
    int i;
    for(i = 0; i < len; i++)
    {
	result += (*(row + i) * *(column + i));
    }
    return result;
}


void nasluchuj()
{
    
}

int main(int argc, char** argv) 
{
    int fd, n, con, petla=1,licznik=0;
    char buf[256],znak;
    struct sockaddr_in sa;
    struct hostent* addrent;
    signal(SIGCHLD, childend);
    float f[2];
    fd = socket(PF_INET, SOCK_STREAM, 0);
    //addrent=gethostbyname("panowiczmichal.ddns.net");
    addrent=gethostbyname("localhost");
    sa.sin_family = PF_INET;
    sa.sin_port = htons(1234);
    memcpy(&sa.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
    while(petla==1)
    {
	con=connect(fd, (struct sockaddr*)&sa, sizeof(sa));
	if(con==-1)
	{
	    printf("Serwer nie odpowiada\n");
	    sleep(5);
	    licznik=licznik+1;
	}
	else 
	{
	    petla=0;
	    int port=htons(1111);
	    printf("%d\n", port);
	    write(fd, &port, sizeof(port));
	    close(fd);
	}
	if(licznik==15)
	{
	    printf("Serwer nie odpowiada zbyt długo. Próbować dalej[y] czy zakończyć program?[inny klawisz] \n");
	    scanf("%c",&znak);
	    if(znak=='y') {licznik=0;}
	    else {return 0;}
	}
    }
    
    int fd3,l,b,fd2,size, on=1,i=0;
    struct sockaddr_in sa1;
    struct sockaddr_in caddr[1];
    signal(SIGCHLD, childend);
    fd3 = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(fd3, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    sa1.sin_family = PF_INET;
    sa1.sin_port = htons(13240);
    sa1.sin_addr.s_addr = INADDR_ANY;
    b=bind(fd3, (struct sockaddr*)&sa1, sizeof(sa1));
    printf("%d\n", b);
    l=listen(fd3,10);
    printf("%d\n", l);
    size=sizeof(caddr[i]);
    while(1)
    {
	fd2=accept(fd3, (struct sockaddr*)&caddr[i], &size);
	if(!fork())
	{
	    close(fd3);
	    printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)caddr[i].sin_addr), caddr[i].sin_port);
	    int len, rowsCount;
	    readI(fd2, &len);
	    readI(fd2, &rowsCount);
	    printf("Rows:%d Columns:%d\n", rowsCount, len);
	    int i;
	    for(i = 0; i < rowsCount * len; i++)
	    {
		float *first, *second;
		int x, y;
		readI(fd2, &x);
		readI(fd2, &y);
		printf("Row:%d Column:%d ", x, y);
		first = readRow(fd2, len);
		second = readRow(fd2, len);
		float result = multiply(first, second, len);
		printf("Value:%f\n", result);
		writeI(fd2, &x);
		writeI(fd2, &y);
		writeF(fd2, &result);
	    }
	}
    }
    
	    //close(fd);
	   // sleep(2);
	    //fd = socket(PF_INET, SOCK_STREAM, 0);
    return 0;
}