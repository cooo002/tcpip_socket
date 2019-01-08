#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // read write 함수를 사용하기 위해 필요한 헤더 파일

 #include <arpa/inet.h>//warning: implicit declaration of function ‘inet_ntop’ 
 // 에러가 뜨면 이 헤더 파일을 추가하자 
 
#define BUF_LEN 128
 
int main(int argc, char *argv[])
{
    int s, n;
    struct sockaddr_in server_addr;
    char buf[BUF_LEN];
   
 
    if(argc!=2)///////////////////////
    {
        printf("usage: %s port\n", argv[0]);
        exit(0);
    }
    
    if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Can't create socket\n");
        exit(0);
    }
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("211.253.49.170");
    // inet_addr() 함수는 숫자와 점으로 이루어진 IP 문자열을 long형의 
    // 숫자 IP 주소로 바꾸어 줍니다
    // struct sockaddr_in 에서 .sin_addr.s_add 값을 long형의
    //  숫자 IP값을 넣어 주어야 하는데 이 때 사용됩니다.
    server_addr.sin_port = htons(atoi(argv[1]));
 
    if(connect(s, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Can't connect.\n");
        exit(0);
    }

    msg = malloc(sizeof(char)*20); //이거 내가 서버로
    // 문자 넘겨주기 위해서 만든것
 
    strcpy(buf, "Hello, Server!");
    write(s, buf, strlen(buf))
    printf(" write text for return server");//
    
  
    while ((n = read(s, buf, BUF_LEN)) > 0)
    {
        buf[n] = '\0';
        printf("%s\n", buf);
    }
    close(s);
}


