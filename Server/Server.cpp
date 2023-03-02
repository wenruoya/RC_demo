#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <stdio.h>
#include <WinSock2.h>  //������
//����
#define LINUX_CMD_REBOOT "reboot"
#define WIN_CMD_REBOOT "shutdown -r -t 0"
//�ػ�
#define LINUX_CMD_SHUTDOWN "shutdown -h 0 "
#define WIN_CMD_SHUTDOWN "shutdown -s -t 0"


#pragma comment(lib,"ws2_32.lib")  //�����  .dll��̬�� .lib��̬��

int main(void) {
	//��ʼ�������
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//�����׽���  AF_INET inet��  SOCK_STREAM tcp  SOCK_DGRAM udp
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	// ���׽���  �趨��ַ�Ͷ˿�
	SOCKADDR_IN serAddr;
	//htonl�ֽ���ת��  �����ֽ���=�������ֽ���
	serAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//Э�����
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(6666);

	bind(server, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));

	//���׼�������Ϊ����ģʽ
	listen(server, 5);  //�������� ����

	//��ѭ��
	while (1)
	{
		SOCKADDR_IN addrClient;
		int len = sizeof(addrClient);
		SOCKET client = accept(server, (sockaddr*)&addrClient, &len);  // �ͻ������ӵ��׽���  �����ͻ���Ϣ
		printf("�ͻ���:%s :%d �����˷�����\n", inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port)); //תΪip��ʽ

		// ��������
		printf("1.����(Linux)\n");
		printf("2.�ػ�(Linux)\n");
		printf("3.����(Windows)\n");
		printf("4.�ػ�(Windows)\n");
		printf("�������������:\n");
		

		int cmd;
		scanf_s("%d", &cmd);
		switch (cmd)
		{
		case 1:  //����
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