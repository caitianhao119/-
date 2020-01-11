#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<WinSock2.h>
#include"message.h"
#include"server.h"
#include"source.h"
using namespace std;
int main()
{
	Server server;
	while (TRUE)
	{

		if (!server.InitSock())   //��ʼ��ʧ��
		{
			cout << "��ʼ��ʧ��" << endl;
		}
		server.sd = server.BindListen();
		if (server.sd == INVALID_SOCKET)
		{
			return -1;
		}
		SOCKET sdListen = server.AcceptConnection(server.sd);
		if (sdListen == INVALID_SOCKET)
		{
			return -1;
		}
		while (server.ProcessConnection(sdListen))
		{
		}
		server.CloseSocket();
	}
	return 0;
}
bool Server::InitSock()   //��ʼ��winsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		cout << "Initiate Socket Success!" << endl;
		return true;
	}
	cout << "Initiate Socket Fail!" << endl;
	return false;
}
SOCKET Server::BindListen()  //���׽���
{
	SOCKET sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == INVALID_SOCKET)
	{
		cout << "Create Socket Fail!" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in sListen;
	sListen.sin_family = AF_INET;
	sListen.sin_addr.s_addr = htonl(INADDR_ANY);
	sListen.sin_port = htons(PORT);
	int nSize;
	nSize = sizeof(sockaddr_in);
	if (bind(sd, (sockaddr*)&sListen, nSize) == SOCKET_ERROR)
	{
		closesocket(sd);
		cout << "��ʧ��" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	if (listen(sd, 10) == SOCKET_ERROR)
	{
		closesocket(sd);
		cout << "����ʧ��" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	return sd;

}
SOCKET Server::AcceptConnection(SOCKET sd)    //���տͻ���
{
	sockaddr_in saRemote;
	int nSize = sizeof(sockaddr_in);
	SOCKET sdListen = accept(sd, (sockaddr*)&saRemote, &nSize);
	if (sdListen == INVALID_SOCKET)
	{
		cout << "���տͻ���ʧ��" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	return sdListen;
}
bool Server::ReceiveFile(SOCKET sd)
{
	char buff[MAX_PACK_SIZE];
	FILE *pFile;
	pFile = fopen(fileName, "a+b");
	_int64 i = 0;
	while (i + 1 < fileLength)
	{
		int nRecv = recv(sd, buff, MAX_PACK_SIZE, 0);
		if (nRecv == SOCKET_ERROR)
		{
			return false;
		}
		fwrite(buff, sizeof(char), nRecv, pFile);
		i += nRecv;
		memset(buff, 0, sizeof(char)*MAX_PACK_SIZE);
	}
	fclose(pFile);
	return true;
}
void Server::CloseSocket()
{
	closesocket(sd);
	WSACleanup();
}
bool Server::ProcessConnection(SOCKET sd)
{
	//���ջ�����
	int nRecvBuf = 2048000;//����Ϊ2000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//���ͻ�����
	int nSendBuf = 2048000;//����Ϊ2000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));


	char buff[MAX_PACK_SIZE];
	Message::MsgHead *msgHead;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "����ʧ��" << WSAGetLastError() << endl;
		return false;
	}
	msgHead = (Message::MsgHead *)&buff;

		switch (msgHead->msgId)
		{
		case MSG_LOGIN:         //�ͻ���������������ļ�
			cout << "�ͻ��������¼" << endl;
			break;
		case MSG_DOWNLOAD_FILE:      //�ͻ��˴ӷ����������ļ�
		{
										 cout << "�ͻ�������ӷ����������ļ�" << endl;
										 Source source;      //������ȡָ���ļ����µ��ļ�
										 string sPath = "D:\\abc";
										 string sExt = ".txt";
										 source.GetFiles(sPath, sExt, source.catalogInfo);
										 int nSize;
										 nSize = source.catalogInfo.size();
										 cout << "�Ѽ���" << nSize << "���ļ�" << endl;
										 char buff[MAX_PACK_SIZE];
										 for (int i = 0; i < nSize; i++)   //��Ŀ¼��Ϣ���͵��ͻ���
										 {
											 strcpy(buff, source.catalogInfo[i].c_str());
											 //cout<<source.catalogInfo[i]<<endl;
											 if (send(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
											 {
												 cout << "����Ŀ¼��Ϣʧ��" << WSAGetLastError() << endl;
												 return false;
											 }
											 Sleep(100);   //˯��100ms�ý��ն˽���Ϣȡ��
										 }
										 Message::MsgComplete msgComplete;
										 if (send(sd, (char *)&msgComplete, sizeof(Message::MsgComplete), 0) == SOCKET_ERROR)
										 {
											 cout << "���������Ϣʧ��" << WSAGetLastError() << endl;
											 return false;
										 }
										 Sleep(100);
										 if (!RecvFileName(sd))
										 {
											 return false;
										 }
										 Sleep(100);
										 if (!GetAndSendFileLength(sd))
										 {
											 return false;
										 }
										 Sleep(100);
										 if (!SendFileName(sd))
										 {
											 return false;
										 }
										 Sleep(100);
										 if (!SendFile(sd))
										 {
											 return false;
										 }
		}
			break;
		case MSG_ACC_PASS:      //�����û���
		{
							   char revAcc[MAX_PACK_SIZE]; //�����û�������
							   int ret = 0; //���ջ������ֽ���
							   Sleep(100);
							   ret = recv(sd, revAcc, MAX_PACK_SIZE -1, 0);
							   if (ret > 0)
							   {
								   revAcc[ret] = '\0';

								   string insAcc = "ctyh123";
								   string insPass = "123456";

								   //�ֽ���û����û���������
								   char Account[100];
								   char Password[100];
								   string cmpACC;
								   string cmpPass;
								   int i = 0;
								   int j = 0 ;
								   while (revAcc[i] != '*')
								   {
									   Account[i] = revAcc[i];
									   i++;
								   }
								   Account[i] = '\0';
								   i++;
								   for (j = 0; i <= ret; i++,j++)
								   {
									   Password[j] = revAcc[i];
								   }

								   cmpACC = Account;
								   cmpPass = Password;

								   if (cmpACC == insAcc && cmpPass == insPass)
								   {
									   send(sd, "TRUE", strlen("TRUE"), 0);
									   cout << "�û��ɹ���¼" << endl;
								   }
								   else
								   { 
									   send(sd, "FALSE", strlen("FALSE"), 0);
									   cout << "�û���¼ʧ��" << endl;
									   closesocket(sd);
								   }
							   }
							   
		}
			break;
		case MSG_FILE:     //���͵��ļ�����
		{
							   cout << "��ʼ�����ļ�" << endl;
							   if (!ReceiveFile(sd))
							   {
								   cout << "�����ļ�ʧ��" << endl;
								   return false;
							   }
		}
			break;
		default:
			return false;
		}
	return true;
}
bool Server::RecvFileName(SOCKET sd)
{
	//memset(fileName,0,sizeof(char)*MAX_FILE_NAME_LENGTH);  //���
	char buff[MAX_PACK_SIZE];
	Message::MsgFileName *msgFileName;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "�����ļ���ʧ��" << WSAGetLastError() << endl;
		return false;
	}
	msgFileName = (Message::MsgFileName *)buff;
	strcpy(fileName, msgFileName->fileName);
	cout << "���յ��ļ���Ϊ" << fileName << endl;
	return true;
}
bool Server::GetAndSendFileLength(SOCKET sd)       //��ȡ�ͻ���Ҫ���ص��ļ�����
{
	Message::MsgFileLength msgFileLength;
	FILE *pFile;
	pFile = fopen(fileName, "r+b");
	if (pFile == NULL)
	{
		cout << "���ļ�ʧ��" << endl;
		return false;
	}
	fseek(pFile, 0, SEEK_END);
	fileLength = _ftelli64(pFile);
	fclose(pFile);
	msgFileLength.fileLength = fileLength;
	if (send(sd, (char*)&msgFileLength, sizeof(Message::MsgFileLength), 0) == SOCKET_ERROR)
	{
		cout << "�����ļ�����ʧ��" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
bool Server::SendFileName(SOCKET sd)       //��ͻ��˷����ļ���
{
	Message::MsgFileName msgFileName;
	char fileDrive[_MAX_DRIVE];
	char fileDir[_MAX_DIR];
	char Name[_MAX_FNAME];
	char fileExt[_MAX_EXT];
	_splitpath(fileName, fileDrive, fileDir, Name, fileExt);
	strcat(Name, fileExt);
	strcpy(msgFileName.fileName, Name);
	cout << "Ҫ���͵��ļ���Ϊ" << Name << endl;
	if (send(sd, (char *)&msgFileName, sizeof(Message::MsgFileName), 0) == SOCKET_ERROR)
	{
		cout << "�����ļ�������" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
bool Server::SendFile(SOCKET sd)  //��ͻ��˷����ļ�
{
	cout << "���뵽�����ļ�����" << endl;
	cout << "Ҫ���͵��ļ�Ϊ" << fileName << endl;
	FILE *pFile;
	pFile = fopen(fileName, "r+b");
	fseek(pFile, 0, SEEK_SET);   //��λ���ļ���λ��
	_int64 i = 0;
	char buff[MAX_PACK_SIZE];
	cout << "Ҫ���͵��ļ�����Ϊ" << fileLength << endl;
	while (i<fileLength)
	{
		int nSize;
		if (i + MAX_PACK_SIZE>fileLength)
		{
			nSize = (int)(fileLength - i);
		}
		else
		{
			nSize = MAX_PACK_SIZE - 1;
		}
		fread(buff, sizeof(char), nSize, pFile);
		int nSend;
		nSend = send(sd, buff, nSize, 0);
		if (nSend == SOCKET_ERROR)
		{
			cout << "����ʧ��" << WSAGetLastError() << endl;
			return false;
		}
		i += nSend;
		fseek(pFile, -(nSize - nSend), SEEK_CUR);  //��λ��ʵ���ѷ��͵���λ��
		memset(buff, 0, sizeof(char)*MAX_PACK_SIZE); //��buff���
	}
	fclose(pFile);
	return true;
}