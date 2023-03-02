#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <stdio.h>
#include <WinSock2.h>  //网络编程
//重启
#define LINUX_CMD_REBOOT "reboot"
#define WIN_CMD_REBOOT "shutdown -r -t 0"
//关机
#define LINUX_CMD_SHUTDOWN "shutdown -h 0 "
#define WIN_CMD_SHUTDOWN "shutdown -s -t 0"


#pragma comment(lib,"ws2_32.lib")  //网络库  .dll动态库 .lib静态库

int main(void) {
	//初始化网络库
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//创建套接字  AF_INET inet网  SOCK_STREAM tcp  SOCK_DGRAM udp
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	// 绑定套接字  设定地址和端口
	SOCKADDR_IN serAddr;
	//htonl字节序转换  主机字节序=》网络字节序
	serAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//协议家族
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(6666);

	bind(server, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));

	//将套件字设置为监听模式
	listen(server, 5);  //三次握手 次数

	//死循环
	while (1)
	{
		SOCKADDR_IN addrClient;
		int len = sizeof(addrClient);
		SOCKET client = accept(server, (sockaddr*)&addrClient, &len);  // 客户端连接的套接字  包含客户信息
		printf("客户端:%s :%d 连接了服务器\n", inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port)); //转为ip形式

		// 交互界面
		printf("1.重启(Linux)\n");
		printf("2.关机(Linux)\n");
		printf("3.重启(Windows)\n");
		printf("4.关机(Windows)\n");
		printf("请输入控制命令:\n");
		

		int cmd;
		scanf_s("%d", &cmd);
		switch (cmd)
		{
		case 1:  //重启
			send(client, LINUX_CMD_REBOOT, sizeof(LINUX_CMD_REBOOT),0);
			break;
		case 2:
			send(client, LINUX_CMD_SHUTDOWN, sizeof(LINUX_CMD_SHUTDOWN), 0);
			break;
		case 3:
			send(client, WIN_CMD_REBOOT, sizeof(WIN_CMD_REBOOT), 0);
			break;
		case 4:
			send(client, WIN_CMD_SHUTDOWN, sizeof(WIN_CMD_SHUTDOWN), 0);
			break;
		}
	}

	return 0;
}