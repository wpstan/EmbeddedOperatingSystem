#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 30

int main(int argc, char **argv)
{
    int sockfd, newfd;
    struct sockaddr_in s_addr, c_addr;
    char buf[BUFLEN];
    socklen_t len;
    unsigned int port, listnum;
    
    // 创建socket
    if((sockfd=socket(AF_INET, SOCK_STREAM,0)) == -1){
        perror("创建socket失败!");
        exit(errno);
    }else
        printf("创建socket成功!\n");

    // 创建端口   
    if(argv[2])
        port = atoi(argv[2]);
    else
        port = 6789;
    // 设置监听队列长度
    if(argv[3])
        listnum = atoi(argv[3]);
    else
        listnum = 3;
    // 设置server端的ip地址
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if(argv[1])
        s_addr.sin_addr.s_addr = inet_addr(argv[1]);
    else
        s_addr.sin_addr.s_addr = INADDR_ANY;
    // 绑定ip和端口到socket
    if((bind(sockfd, (struct sockaddr*) &s_addr,sizeof(struct sockaddr))) == -1){
        perror("绑定失败!");
        exit(errno);
    }else
        printf("绑定成功\n");
    // 监听本地端口
    if(listen(sockfd,listnum) == -1){
        perror("监听失败!");
        exit(errno);    
    }else
        printf("服务器正在监听中...\n");
    while(1){
        len = sizeof(struct sockaddr);
        if((newfd = accept(sockfd,(struct sockaddr*) &c_addr, &len)) == -1){
            perror("连接失败!");        
            exit(errno);
        }else
            printf("正在绑定客户端: %s: %d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
        while(1){
        
            //绑定成功,接受消息
            bzero(buf,BUFLEN);
            len = recv(newfd,buf,BUFLEN,0);
			char tempstr[30];
			bzero(tempstr,30);
            if(len > 0){
                printf("从客户端收到的消息：%s\n",buf);
				if(strstr(buf,"ADD")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d + %d = %d",a,b,a+b);
				}				
				if(strstr(buf,"SUB")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d - %d = %d",a,b,a-b);
				}				
				if(strstr(buf,"MUL")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d x %d = %d",a,b,a*b);
				}				
				if(strstr(buf,"DIV")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d / %d = %d",a,b,a/b);
				}				

				send(newfd,tempstr,strlen(tempstr),0);
			}

            else{
                if(len < 0 )
                    printf("接收消息失败！\n");
                else
                    printf("客户端已经关闭\n");
                break;        
            }
	
        }
        //关闭server的socket
        close(newfd);
        //判断是否退出server
        printf("是否退出服务器?y/n?");
        bzero(buf, BUFLEN);
        fgets(buf,BUFLEN, stdin);
        if(!strncasecmp(buf,"y",1)){
            printf("关闭服务器!\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
