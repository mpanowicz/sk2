#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256
#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

float* readRow(int fd, int len){
    static float *row  = NULL;
    row = (float *)calloc( len , sizeof(calloc) );
    read(fd, row, sizeof(float) * len);
	int i;
	for(i = 0; i < len; i++){
		printf("%f ", row[i]);
	}
	printf("\n");
    if (row == NULL){
        printf("Error");
    }
    return row;
}

float multiply(float* row, float* column, int len){
    float result;
    result = 0;
    int i;
    for(i = 0; i < len; i++){
        result += (*(row + i) * *(column + i));
    }
    return result;
}

int main(int argc, char** argv) {
	while(1){
		int fd, con = 0;
		struct sockaddr_in sa;
		struct hostent* addrent;
		fd = socket(PF_INET, SOCK_STREAM, 0);
		addrent=gethostbyname(argv[1]);
		sa.sin_family = PF_INET;
		sa.sin_port = htons(1234);
		memcpy(&sa.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
		con = connect(fd, (struct sockaddr*)&sa, sizeof(sa));
		if(con == 0){
			int len, rowsCount;
			readI(fd, &len);
			readI(fd, &rowsCount);
			printf("Rows:%d Columns:%d\n", rowsCount, len);
			int i;
			for(i = 0; i < rowsCount * rowsCount; i++){
				float *first, *second;
				int x, y;
				readI(fd, &x);
				readI(fd, &y);
				printf("Row:%d Column:%d \n", x, y);
				first = readRow(fd, len);
				second = readRow(fd, len);
				float result = multiply(first, second, len);
				printf("Value:%f\n", result);
				writeI(fd, &x);
				writeI(fd, &y);
				writeF(fd, &result);
			}
		}
		close(fd);
	}
    return 0;
}
