#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define SERVER_IP "172.20.10.7"
#define PORT  8800
class QUESTFILE2
{
public:
	_int64 nFileLength;
	char fileName[_MAX_FNAME + _MAX_EXT];
	SOCKET sd;
	bool InitSock();   //��ʼ��winsock
	u_long ResolveAdress(char *serverIp);    //������������ַ
	SOCKET ConnectServer(u_long serverIp, int port);//���ӷ�����
	bool ProcessConnection(SOCKET sd);    //�ͻ��˷���������
	void CloseSocket();         // �ر��׽���
	bool RecvCatalogInfo(SOCKET sd);     //����Ŀ¼��Ϣ
	bool SendDownLoadFileName(SOCKET sd);  //����Ҫ���ص��ļ���
	bool ReceiveFileLength(SOCKET sd);    //�����ļ�����
	bool ReceiveFileName(SOCKET sd);   //�����ļ���
	bool ReceiveFile(SOCKET sd);      //�����ļ�
	//void DoWork();       //���庯��
};

