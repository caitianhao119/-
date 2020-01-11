#include "QtGuiApplication2.h"

int questmainmenu();
MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)  //股票列表
{
	//窗口初始化配置
	this->resize(1800, 800);
	this->setWindowTitle("股票列表");
	this->setStyleSheet("background-color: rgb(0,0,0)");
	int columncount = 29;
	int rowcount = 2000;

	//创建表格置于窗口中，调整参数
	QTableWidget * maintable = new QTableWidget(this);
	setCentralWidget(maintable);
	maintable->setRowCount(rowcount);
	maintable->setColumnCount(columncount);
	maintable->resize(1600, 800);
	maintable->horizontalHeader()->setMinimumSectionSize(45);
	maintable->horizontalHeader()->setMaximumSectionSize(45);
	maintable->resizeRowsToContents();
	maintable->verticalHeader()->setVisible(false);
	maintable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:black;font:8pt '宋体';color: white;}");
	maintable->setStyleSheet("color: white");
	maintable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	maintable->setSelectionBehavior(QAbstractItemView::SelectRows);
	maintable->setSelectionMode(QAbstractItemView::SingleSelection);
	maintable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	maintable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	maintable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	QStringList header;
	header << "股票"<<"股票代码"<<"股票名称"<<"昨日收盘价"<<"昨日结算价"<<"昨日持仓量"<<"涨停价"<<"跌停价"<<"总股本"<<"流通盘"
		<<"合约数量乘数"<<"最小变动价位"<<"上市日"<<"到期日"<<"合约在RZRK的代码"<<"合约在交易所的代码"<<"利息额"<<"除权除息"<<"停牌"<<"创建日"
		<<"限价单最大下单量（买）"<<"限价单最小下单量（买）"<<"投资者适当性管理分类"<<"最小回购天数"<<"最大回购天数"<<"证券类型" <<"证券种类和属性高位"<<"证券种类和属性低位"<<"要约收购信息";
	maintable->setHorizontalHeaderLabels(header);//设置表头

	//若本地无mainmenu文件向系统申请文件
	FILE* fp = fopen("D:/shixi/shili/StockSystem/QtGuiApplication2/test1.txt", "r");
	if (fp == NULL)
	{
		int quest = questmainmenu();
		if (quest == 0)
		{
			QMessageBox::information(this, tr("404，sorry"), tr("客户端下载数据失败！"));
		}
	}

	//打开文件并按行读取将数据存于表格中
	QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test1.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404，sorry"), tr("数据加载失败！"));
	}
	QTextStream in(&file);
	QString line = in.readLine();
	QString linepresent = line;
	int rowpresent = 0;
	while (!line.isNull())
	{
		QStringList list = line.split("\t");
		for (int columnpresent = 0; columnpresent < 28; columnpresent++)
		{
			QTableWidgetItem *item = new QTableWidgetItem();
			item->setText(list[columnpresent]);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			if (columnpresent == 1)
				item->setTextColor(QColor(128, 255, 255));
			if (columnpresent == 2)
				item->setTextColor(QColor(Qt::yellow));
			if (columnpresent == 3)
				item->setTextColor(QColor(200, 111, 100));
			if (columnpresent == 6)
				item->setTextColor(QColor(Qt::red));
			if (columnpresent == 7)
				item->setTextColor(QColor(Qt::green));
			if (columnpresent == 12)
				item->setTextColor(QColor(Qt::red));       //设置各列字体
			maintable->setItem(rowpresent, columnpresent, item);
		}
		rowpresent++;
		line = in.readLine();
	}
	
	//将第一行的股票名称一栏设为按钮，调整格式
	Mybtn *pBtn = new Mybtn(); 
	QStringList list = linepresent.split("\t");
	pBtn->setText(list[2]);
	pBtn->setStyleSheet("color: yellow");
	connect(pBtn, SIGNAL(doubleClicked()),this, SLOT(SlotSpecific()));
	maintable->setCellWidget(0, 2, pBtn);
	
	//使表格可以根据窗口大小放缩
	QHBoxLayout *windowLayout = new QHBoxLayout;  
	windowLayout->addWidget(maintable); 
	setCentralWidget(maintable);
	this->setLayout(windowLayout);
	this->show();
}

void MainMenu::SlotSpecific()
{
	this->hide();
	m = new ConditionMenu;
	connect(m->btn1, SIGNAL(clicked()), this, SLOT(SlotReshow()));//下一个窗口返回时的信号接收槽
}

void MainMenu::SlotReshow()
{
	this->show();
}

int questmainmenu()
{
	QUESTFILE client;
	if (!client.InitSock())
	{
		//cout << "初始socket失败" << endl;
		return 0;
	}
	SOCKET saRemote = client.ConnectServer(client.ResolveAdress(SERVER_IP), PORT);
	if (saRemote == INVALID_SOCKET)
	{
		//cout << "连接服务器失败" << endl;
		return 0;
	}
	if (!client.ProcessConnection(saRemote))
	{
		return 0;
	}
	client.CloseSocket();
	return 1;
}
bool QUESTFILE::InitSock()    //初始socket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long QUESTFILE::ResolveAdress(char *serverIp)   //解析IP地址
{
	u_long nAddr = inet_addr(serverIp);
	if (nAddr == INADDR_NONE)  //表明serverIp使用的是主机名形式
	{
		hostent *ent = gethostbyname(serverIp);
		if (ent == NULL)
		{
			cout << "获取主机名出错" << WSAGetLastError() << endl;
		}
		else
		{
			nAddr = *((u_long *)ent->h_addr_list[0]);
		}
	}
	if (nAddr == INADDR_NONE)
	{
		cout << "解析主机地址失败" << endl;
	}
	return nAddr;
}
SOCKET QUESTFILE::ConnectServer(u_long serverIp, int port)   //连接服务器
{
	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == INVALID_SOCKET)
	{
		cout << "创建套接字失败" << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = serverIp;
	saServer.sin_port = htons(port);
	if (connect(sd, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "连接服务器失败" << WSAGetLastError() << endl;
		closesocket(sd);
		return INVALID_SOCKET;
	}
	return sd;
}
bool QUESTFILE::ProcessConnection(SOCKET sd)      //进行通信
{
	//系统缓冲区
	int nRecvBuf = 2048000;//设置为2000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//发送缓冲区
	int nSendBuf = 2048000;//设置为2000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	Message::MsgDownLoadFile msgDownLoadFile;
	if (send(sd, (char *)&msgDownLoadFile, sizeof(Message::MsgDownLoadFile), 0) == SOCKET_ERROR)
	{
		cout << "发送下载文件消息失败" << WSAGetLastError() << endl;
		return false;
	}
	if (!RecvCatalogInfo(sd))
	{
		return false;
	}
	if (!SendDownLoadFileName(sd))
	{
		return false;
	}
	if (!ReceiveFileLength(sd))
	{
		return false;
	}
	if (!ReceiveFileName(sd))
	{
		return false;
	}
	if (!ReceiveFile(sd))
	{
		return false;
	}

	return true;
}
bool QUESTFILE::RecvCatalogInfo(SOCKET sd)   //接收目录信息
{
	int flag = 1;     //接收目录信息成功标志
	char buff[MAX_PACK_SIZE];
	Message::MsgHead *msgHead;
	while (true)
	{
		if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
		{
			cout << "接收目录信息失败" << WSAGetLastError() << endl;
			flag = 0;
			break;
		}
		msgHead = (Message::MsgHead *)buff;
		if (msgHead->msgId == MSG_COMPLETE)      //判断消息是否是标准消息
		{
			cout << "目录信息发送完成" << endl;
			break;
		}
		else
		{
			cout << buff << endl;     //发送来的是目录信息，即文件名
		}
	}
	if (flag == 0)
	{
		return false;
	}
	return true;
}
bool QUESTFILE::SendDownLoadFileName(SOCKET sd)      //发送下载的文件名
{
	cout << "请输入你要下载的文件名" << endl;
	char fileName[_MAX_FNAME + _MAX_EXT] = "D:\\StockData\\test1.txt";
	Message::MsgFileName msgFileName;
	strcpy(msgFileName.fileName, fileName);
	if (send(sd, (char *)&msgFileName, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "发送下载文件名出错" << WSAGetLastError() << endl;
		system("pause");
		return false;
	}
	return true;
}
bool QUESTFILE::ReceiveFileLength(SOCKET sd)     //接收下载的文件长度
{
	Sleep(100);
	char buff[MAX_PACK_SIZE];
	Message::MsgFileLength *msgFileLength;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "接收文件长度失败" << WSAGetLastError() << endl;
		return false;
	}
	msgFileLength = (Message::MsgFileLength *)buff;
	nFileLength = msgFileLength->fileLength;
	cout << "接收到文件长度" << nFileLength << endl;

	return true;
}
bool QUESTFILE::ReceiveFileName(SOCKET sd)   //接收下载的文件名
{
	Sleep(100);
	char buff[MAX_PACK_SIZE];
	memset(fileName, 0, sizeof(char)*(_MAX_FNAME + _MAX_EXT));
	Message::MsgFileName *msgFileName;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "接收文件名出错" << endl;
		return false;
	}
	msgFileName = (Message::MsgFileName *)buff;
	strcpy(fileName, msgFileName->fileName);
	cout << "接收到文件名" << fileName << endl;
	return true;
}
bool QUESTFILE::ReceiveFile(SOCKET sd)      //接收文件内容
{
	char buff[MAX_PACK_SIZE];
	FILE *pFile;
	pFile = fopen(fileName, "a+b");
	_int64 i = 0;
	while (i + 1 < nFileLength)
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
void QUESTFILE::CloseSocket()   //关闭套接字
{
	closesocket(sd);
	WSACleanup();
}
