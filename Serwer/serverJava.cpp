#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>

#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

using namespace std;

void childend(int signum)
{
	wait(NULL);
	printf("Koniec połączenia\n");
}

void remove(int signum){
	system("rm -rf files/");
	exit(0);
}

void getFile(char path[100], int jfdc){
	char buf[1000];
	int fd = open(path, O_RDWR | O_CREAT, 0666);
	int n = 0;
	n = read(jfdc, &buf, 1000);
	while(n > 0){
		cout<<buf<<endl;
		write(fd, &buf, n);
		memset(&buf[0], 0, sizeof(buf));
		n = read(jfdc, &buf, 1000);
		if(strcmp(buf, "end") == 0){
			break;
		}
	}
	close(fd);
}

int main(int argc, char** argv) {
	mkdir("./files", 0777);
    unsigned int jfd, jfdc, size, on=1;
    struct sockaddr_in jsa;
    struct sockaddr_in caddr;
	if (signal (SIGINT, remove) == SIG_IGN)
		signal (SIGINT, SIG_IGN);
	if(signal(SIGCHLD, childend) == SIG_IGN)
		signal(SIGCHLD, SIG_IGN);
    jfd = socket(PF_INET, SOCK_STREAM, 0);
	setsockopt(jfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    jsa.sin_family = PF_INET;
    jsa.sin_port = htons(1234);
    jsa.sin_addr.s_addr = INADDR_ANY;
	
    bind(jfd, (struct sockaddr*)&jsa, sizeof(jsa));
	listen(jfd,10);
	size=sizeof(caddr);

	while(1){
        jfdc=accept(jfd, (struct sockaddr*)&caddr, &size);
        if(!fork()){
            close(jfd);
            printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)caddr.sin_addr), caddr.sin_port);
			char path[100];
			sprintf(path, "./files/%d", caddr.sin_port);
			mkdir(path, 0777);
			sprintf(path, "./files/%d/macierzA.txt", caddr.sin_port);
			getFile(path, jfdc);
			sprintf(path, "./files/%d/macierzB.txt", caddr.sin_port);
			getFile(path, jfdc);
			close(jfdc);
			return 0;
        }

	}
	close(jfd);
    return 0;
}