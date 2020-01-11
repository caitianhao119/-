#pragma once
#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<fstream>
#include<vector>
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define SERVER_IP "172.20.10.7"
#define PORT  8800
class Client
{
public:
	_int64 nFileLength;
	char fileName[_MAX_FNAME + _MAX_EXT];
	SOCKET sd;
	bool InitSock();   //��ʼ��winsock
	u_long ResolveAdress(char *serverIp);    //������������ַ
	SOCKET ConnectServer(u_long serverIp, int port);//���ӷ�����
	bool SendAccountAndPass(SOCKET sd, const char acc[], const char pass[]); //�����û���
	bool ProcessConnection(SOCKET sd,const char acc[] ,const char pass[]);    //�ͻ��˷���������
	void CloseSocket();         // �ر��׽���
	//void DoWork();       //���庯��
};

