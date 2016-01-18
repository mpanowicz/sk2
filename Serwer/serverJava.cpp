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
#include <vector>
#include <sstream>
#include <fstream>

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
	printf("Writing to: %s\n", path);
	char buf[1000];
	int fd = open(path, O_RDWR | O_CREAT, 0666);
	int n = 0;
	n = read(jfdc, &buf, 1);
	while(n > 0){
		write(fd, &buf, n);
		memset(&buf[0], 0, sizeof(buf));
		n = read(jfdc, &buf, 1);
		if(buf[0] == 'e'){
			break;
		}
	}
	close(fd);
}

vector< vector<float> > readFile(char path[100]){
	fstream in(path);
	string line;
	vector< vector<float> > v;
	int i = 0;
	
	while (std::getline(in, line))
    {
        float value;
        std::stringstream ss(line);
        v.push_back(vector<float>());

        while (ss >> value)
        {
            v[i].push_back(value);
        }
        ++i;
    }
	return v;
}

float* vecToFloat(vector<float> v){
	static float *row  = NULL;
    row = (float *)calloc( v.size() , sizeof(sizeof(v)) );
    memcpy(row, &v[0], v.size() * sizeof(v[0]));
	for(int i = 0; i < v.size(); i++){
		cout<<row[i]<<" ";
	}
	printf("\n");
    if (row == NULL){
        printf("Error");
    }
    return row;
}

int main(int argc, char** argv) {
	mkdir("./files", 0777);
    unsigned int jfd, jfdc, lfdc, size, on=1;
    struct sockaddr_in jsa, lsa;
    struct sockaddr_in caddr, laddr;
	if (signal (SIGINT, remove) == SIG_IGN)
		signal (SIGINT, SIG_IGN);
	if(signal(SIGCHLD, childend) == SIG_IGN)
		signal(SIGCHLD, SIG_IGN);
    jfd = socket(PF_INET, SOCK_STREAM, 0);
	setsockopt(jfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    jsa.sin_family = PF_INET;
    jsa.sin_port = htons(4321);
    jsa.sin_addr.s_addr = INADDR_ANY;
	bind(jfd, (struct sockaddr*)&jsa, sizeof(jsa));
	listen(jfd, 10);
	
	lfdc = socket(PF_INET, SOCK_STREAM, 0);
	lsa.sin_family = PF_INET;
	lsa.sin_port = htons(1234);
	lsa.sin_addr.s_addr = INADDR_ANY;
	bind(lfdc, (struct sockaddr*)&lsa, sizeof(lsa));
	listen(lfdc, 10);
	
	size=sizeof(caddr);

	while(1){
        jfdc=accept(jfd, (struct sockaddr*)&caddr, &size);
        if(!fork()){
            close(jfd);
            printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)caddr.sin_addr), caddr.sin_port);
			char path[100], pathA[100], pathB[100];
			sprintf(path, "./files/%d", caddr.sin_port);
			mkdir(path, 0777);
			sprintf(pathA, "./files/%d/macierzA.txt", caddr.sin_port);
			getFile(pathA, jfdc);
			sprintf(pathB, "./files/%d/macierzB.txt", caddr.sin_port);
			getFile(pathB, jfdc);
			vector< vector<float> > a = readFile(pathA);
			vector< vector<float> > b = readFile(pathB);
			int fd2;
			while(1){
				fd2 = accept(lfdc, (struct sockaddr*)&laddr, &size);
				if(!fork()){
					close(lfdc);
					printf("Nowe połączenie: %s:%i\n", inet_ntoa((struct in_addr)laddr.sin_addr), laddr.sin_port);
					int len = a[0].size();
					int rowsCount = a.size();
					int portCast = (int) laddr.sin_port;
					writeI(fd2, &len);
					writeI(fd2, &rowsCount);
					//writeI(fd2, &portCast);
					int i, j;
					for(i = 0; i < rowsCount; i++){
						for(j = 0; j < len; j++){
							writeI(fd2, &i);
							writeI(fd2, &j);
							float mA[1000], mB[1000];
							copy(a[i].begin(), a[i].end(), mA);
							copy(b[j].begin(), b[j].end(), mB);
							write(fd2, mA, sizeof(float) * len);
							write(fd2, mB, sizeof(float) * len);
							float result;
							int x, y, port;
							readI(fd2, &x);
							readI(fd2, &y);
							readF(fd2, &result);
							//readI(fd2, &port);
							printf("Port:%d Row:%d Column:%d Value:%f PortC:%d\n", laddr.sin_port, x, y, result, port);
						}
					}
					write(fd2, "\n", 1);
					close(fd2);
					break;break;
				}
			}
			close(jfdc);
			return 0;
        }
		
	}
	close(jfd);
    return 0;
}