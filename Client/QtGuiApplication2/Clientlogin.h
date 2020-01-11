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
	bool InitSock();   //初始化winsock
	u_long ResolveAdress(char *serverIp);    //解析服务器地址
	SOCKET ConnectServer(u_long serverIp, int port);//连接服务器
	bool SendAccountAndPass(SOCKET sd, const char acc[], const char pass[]); //发送用户名
	bool ProcessConnection(SOCKET sd,const char acc[] ,const char pass[]);    //客户端服务器交互
	void CloseSocket();         // 关闭套接字
	//void DoWork();       //主体函数
};

