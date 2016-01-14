#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_SIZE 256

float* readRow(int fd, int len){
    static float *row  = NULL;
    //row = malloc(sizeof(float) * len);
    row = (float *)calloc( len , sizeof(calloc) );
    //memset(row, 0, sizeof(float) * len);
    read(fd, row, sizeof(float) * len);
    if (row == NULL){
        printf("Error");
    }
	int i;
	for(i = 0; i < len; i++){
        printf("%f\n", *(row + i));
	}
    return row;
}

int main(int argc, char** argv) {
    //gniazdo strumieniowe - TCP - sock_stream
    //gniazko datagramowe - UDP - sock_dgam
    //socket zwraca deskryptor do pliku
	int fd, n;
    char buf[256];
    struct sockaddr_in sa;
	struct hostent* addrent;
	float f[2];
    fd = socket(PF_INET, SOCK_STREAM, 0);
	addrent=gethostbyname("localhost");
    //socket address - socket
    sa.sin_family = PF_INET;
    //konwersja portu 80 z repr. lokalnej do sieciowej do 16 bitow
    sa.sin_port = htons(1234);
    //inet_addr tlumaczy XX.XX.XX.XX na ciag 32 bitow
    //sa.sin_addr.s_addr = inet_addr(argv[1]);
	memcpy(&sa.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
    connect(fd, (struct sockaddr*)&sa, sizeof(sa));
	//write(fd, argv[1], 6);
	int len;
	n = read(fd, &len, sizeof(len));
	float *rowA, *rowB;
	rowA = readRow(fd, len);
    rowB = readRow(fd, len);
    int i;
    for(i = 0; i < len; i++){
        printf("%f\n", *(rowB + i));
	}
	printf("%d\n", len);
    close(fd);
    return 0;
}
