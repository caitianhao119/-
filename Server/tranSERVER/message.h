#pragma once
#include<iostream>
using namespace std;
#define MAX_PACK_SIZE  10240   //数据包的长度
#define MAX_FILE_NAME_LENGTH 256  //文件名的长度
#define INVALID_MSG -1       //无效的消息
#define MSG_FILE_LENGTH 1    //文件长度
#define MSG_FILE_NAME 2    //文件名
#define MSG_FILE   4     //文件内容
#define MSG_READY   3     //准备好消息
#define MSG_LOGIN 5  //用户登录
#define MSG_ACC_PASS 8 //用户名与密码
#define MSG_DOWNLOAD_FILE 6  //下载文件
#define MSG_COMPLETE 7     //完成信息
class Message
{
public:
	struct MsgHead     //头消息
	{
		int msgId;    //消息标识
		MsgHead(int msg = INVALID_MSG) :msgId(msg){};
	};
	struct MsgFileLength :public MsgHead
	{
		_int64 fileLength;   //文件长度
		MsgFileLength() :MsgHead(MSG_FILE_LENGTH){}
	};
	struct MsgFileName :public MsgHead
	{
		char fileName[MAX_FILE_NAME_LENGTH];
		MsgFileName() :MsgHead(MSG_FILE_NAME){}
	};
	struct MsgFile :public MsgHead
	{
		MsgFile() :MsgHead(MSG_FILE){}
	};
	struct MsgReady :public MsgHead        //准备好消息
	{
		MsgReady() :MsgHead(MSG_READY){}
	};
	struct MsgLogin :public MsgHead  //发送文件消息
	{
		MsgLogin() :MsgHead(MSG_LOGIN){}
	};
	struct MsgDownLoadFile :public MsgHead     //下载文件消息
	{
		MsgDownLoadFile() :MsgHead(MSG_DOWNLOAD_FILE){}
	};
	struct MsgComplete :public MsgHead //完成
	{
		MsgComplete() :MsgHead(MSG_COMPLETE){}
	};
	struct MsgAccPass :public MsgHead //用户名密码
	{
		MsgAccPass() :MsgHead(MSG_ACC_PASS){}
	};
};