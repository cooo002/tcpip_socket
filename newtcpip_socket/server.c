#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // read write 함수를 사용하기 위해 필요한 헤더 파일
#include "netinet/in.h"//inet_pton, inet_ntop 함수가 포함된 헤더파일
#include <arpa/inet.h>//warning: implicit declaration of function ‘inet_ntop’ 
 // 에러가 뜨면 이 헤더 파일을 추가하자 
#define BUF_LEN 128


//  터미널에서 파일을 삭제하고 싶다면 rm 파일 이름 
// *here is commit check Point*
 
int main(int argc, char *argv[])
{
    char buffer[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int server_fd, client_fd;
    int msg_size;
    socklen_t len; // 내가 반환형을 socklen_t 로 변환해준것 
    if(argc!=2)
    {
        printf("usage : %s [port]\n", argv[0]);
        exit(0);
    }
 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        printf("Server : Can't open stream socket\n");
        exit(0);
    }
    memset(&server_addr, 0x00, sizeof(server_addr));
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // ip주소롤 어떤것이든 사용힐 수 있게 해주기 위해INADDR_AN 
    // 사용
    server_addr.sin_port = htons(atoi(argv[1]));
 ////////////////////////////////////////////////////
    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Server : Can't bind local address.\n");
        exit(0);
    }
 //위 부분은 bind()함수를 이용하여 socket에 server socket에 필요한
 // 정보를 할당하고 커널에 등록

 ///////////////////////////////////////////////////
    if(listen(server_fd, 5) < 0)
    {
        printf("Server : Can't listening connect.\n");
        exit(0);
    }
    ////listen() 함수로 클라이언트 접속 요청을 확인합니다. /////

    memset(buffer, 0x00, sizeof(buffer));
    printf("Server: waiting...\n");
    len = sizeof(client_addr);
 
    while(1)
    {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
        if(client_fd < 0)
        {
            printf("Server: accept failed.\n");
            exit(0);
        }
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
        printf("Server: %s client connected.\n", temp);
 
        msg_size = read(client_fd, buffer, 1024);
        printf("client msg: %s\n", buffer);
        strcpy(buffer, "Merry Christmas!");
        msg_size = strlen(buffer);
        write(client_fd, buffer, msg_size);
        close(client_fd);
        printf("Server: %s client closed.\n", temp);
    }
    close(server_fd);
    return 0;
}
