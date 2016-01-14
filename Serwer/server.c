#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

//SERWER: socket() -> bind()-> listen() -> accept() -> write()/read() -> close() ->accept()
void childend()
{
    wait(NULL);
    printf("*** End of child process\n");
}


int main(int argc, char** argv) {
    //gniazdo strumieniowe - TCP - sock_stream
    //gniazko datagramowe - UDP - sock_dgam
    //socket zwraca deskryptor do pliku
    int fd, n , b,l,fd2,size, on=1;
    char buf[6],buf2[6]={1,1,7,1,9,3};
    struct sockaddr_in sa;
    struct sockaddr_in caddr[atoi(argv[1])];
	signal(SIGCHLD, childend);
    fd = socket(PF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    //socket address - socket
    sa.sin_family = PF_INET;
    //konwersja portu 80 z repr. lokalnej do sieciowej do 16 bitow
    sa.sin_port = htons(1234);
    //inet_addr tlumaczy XX.XX.XX.XX na ciag 32 bitow
    sa.sin_addr.s_addr = INADDR_ANY;

    b=bind(fd, (struct sockaddr*)&sa, sizeof(sa));
	l=listen(fd,10);
	size=sizeof(caddr[0]);
	while(1){
        fd2=accept(fd, (struct sockaddr*)&caddr[0], &size);
        if(!fork()){
            close(fd);
            printf("nowe polaczenie: %s:%i\n", inet_ntoa((struct in_addr)caddr[0].sin_addr), caddr[0].sin_port);
            float tab[3] = {1.0, 2.0, 3};
            int i;
            int x;
            x = sizeof(tab)/sizeof(float);
            write(fd2, &x, sizeof(int));
            write(fd2, tab, sizeof(tab));
            write(fd2, tab, sizeof(tab));
            printf("%d\n", x);
            write(fd2, "\n", 1);
            close(fd2);
            return 0;
        }

        close(fd2);
	}
	close(fd);
    return 0;
}
