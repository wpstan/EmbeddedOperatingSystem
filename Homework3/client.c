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
    int sockfd;
    struct sockaddr_in s_addr;
    socklen_t len;
    unsigned int port;
    char buf[BUFLEN];    
    
    // 建立socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("创建socket失败!");
        exit(errno);
    }else
        printf("创建socket成功!\n");

    // 创建端口 
    if(argv[2])
        port = atoi(argv[2]);
    else
        port = 6789;
    // 设置服务器的ip地址
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if (inet_aton(argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr) == 0) {
        perror(argv[1]);
        exit(errno);
    }
    // 连接服务器   
    if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) == -1){
        perror("连接服务器失败!");
        exit(errno);
    }else
        printf("连接服务器成功!\n");
    
    while(1){
	// 开始给服务器发送消息
        bzero(buf,BUFLEN);
        printf("请选择需要计算的类型：\n");
        printf("1: (加)ADD\n");
        printf("2: (减)SUB\n");
        printf("3: (乘)MUL\n");
        printf("4: (除)DIV\n");
        printf("5: (退出)QUIT\n");
		int a=0, b=0, op=0;
		char *option;
		scanf("%d",&op);
		switch(op)
		{
			case 1:{
				   option = "ADD";
				   break;
				   }
			case 2:{
				   option = "SUB";
				   break;
				   }
			case 3:{
				   option = "MUL";
				   break;
				   }
			case 4:{
				   option = "DIV";
				   break;
				   }
			case 5:{
				   printf("关闭客户端!\n");
				   break;
				   }
		}
		if(op == 5){
			break;
		}
		printf("请输入第一个运算数: ");
		scanf("%d",&a);

		printf("请输入第二个运算数: ");
		scanf("%d",&b);
	
		while (op==4&&b==0){
			printf("除数不能为0,请重新输入:");
	
			scanf("%d",&b);
		}
		sprintf(buf,"%d,%d,%s",a,b,option);
	
      
        if(strchr(buf,'\n'))
            len = send(sockfd,buf,strlen(buf)-1,0);
        else
            len = send(sockfd,buf,strlen(buf),0);
        if(len > 0)
            printf("发送成功!\n");            
        else{
            printf("发送失败!\n");
            break;            
        }
        // 接收服务器端消息
        bzero(buf,BUFLEN);
        len = recv(sockfd,buf,BUFLEN,0);
        if(len > 0)
            printf("成功接收服务器端返回消息,计算结果为:%s\n",buf);
        else{
            if(len < 0 )
                printf("接收失败!\n");
            else
                printf("服务器端关闭\n");
            break;    
        }
   
    }
    close(sockfd);

    return 0;
}
