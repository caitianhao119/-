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
	bool InitSock();   //初始化winsock
	u_long ResolveAdress(char *serverIp);    //解析服务器地址
	SOCKET ConnectServer(u_long serverIp, int port);//连接服务器
	bool ProcessConnection(SOCKET sd);    //客户端服务器交互
	void CloseSocket();         // 关闭套接字
	bool RecvCatalogInfo(SOCKET sd);     //接收目录信息
	bool SendDownLoadFileName(SOCKET sd);  //发送要下载的文件名
	bool ReceiveFileLength(SOCKET sd);    //接收文件长度
	bool ReceiveFileName(SOCKET sd);   //接收文件名
	bool ReceiveFile(SOCKET sd);      //接收文件
	//void DoWork();       //主体函数
};

