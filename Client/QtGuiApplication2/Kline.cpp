#include "QtGuiApplication2.h"

int questKline();
Kline::Kline(QWidget *parent)
	: QMainWindow(parent) //k线窗口
{
	//窗口数据格式初始化 
	this->resize(1800, 800);
	this->setWindowTitle("000001 平安银行");

	//k线窗口QCustomPlot横纵坐标轴数据处理
	QCustomPlot *customPlot = new QCustomPlot(this);
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	QDateTime start = QDateTime(QDate(2019,1,1)); //初始时间
	QDateTime end = QDateTime(QDate(2019,12,31));  //末时间
	double startTime = start.toTime_t();
	double endTime = end.toTime_t();
	double binSize = 3600 * 24;  //日k图，一格一天
	QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
	dateTimeTicker->setDateTimeSpec(Qt::UTC);
	dateTimeTicker->setDateTimeFormat("yyyy-M-d"); //设置时间格式
	dateTimeTicker->setTickCount(30); 
	customPlot->xAxis->setTicker(dateTimeTicker);
	customPlot->xAxis->setTickLabelRotation(15);
	customPlot->xAxis->setRange(startTime,endTime);
	QSharedPointer<QCPAxisTicker> tickertext(new QCPAxisTicker);
	tickertext->setTickCount(15);
	customPlot->yAxis->setTicker(tickertext);
	customPlot->yAxis->setRange(5.00, 25.00);  //y轴范围

	//若本地无kline文件向系统申请文件
	FILE* fp = fopen("D:/shixi/shili/StockSystem/QtGuiApplication2/test4.txt", "r");
	if (fp == NULL)
	{
		int quest = questKline();
		if (quest == 0)
		{
			QMessageBox::information(this, tr("404，sorry"), tr("客户端下载数据失败！"));
		}
	}

	//打开文件准备进行绘制
	QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test4.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404，sorry"), tr("数据加载失败！"));
	}
	QTextStream in(&file);
	QString line = in.readLine();
	QStringList list = line.split("\t");

	//按行处理数据，绘制2019一整年的日k图。
	//用容器存储每个时刻的时间和股票价格。
	QVector<double> time, value1;
	while (!line.isNull())
	{
		QStringList list = line.split("\t");
		QDateTime thistime;
		thistime = QDateTime::fromString(list[0], "yyyy-MM-ddhh:mm:ss");
		double thisday = thistime.toTime_t();
		for (int i = 0; i < 4; i++)
		{
			double thisdaynew = thisday + i * 5;
			time.push_back(thisdaynew);
			double data = list[i+1].toDouble();
			value1.push_back(data);
		}                      
		line = in.readLine();
	}

	//用QCustomPlot自带的类和函数进行k线绘制
	QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
	candlesticks->setName("Candlestick");
	candlesticks->setChartStyle(QCPFinancial::csCandlestick);
	candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
	candlesticks->setWidth(binSize*0.9);  //每个k线格宽度
	candlesticks->setTwoColored(true);
	candlesticks->setBrushPositive(QColor(Qt::red));
	candlesticks->setBrushNegative(QColor(Qt::green));
	candlesticks->setPenPositive(QPen(QColor(Qt::red)));
	candlesticks->setPenNegative(QPen(QColor(Qt::green)));
	setCentralWidget(customPlot);

	//返回上一层窗口按钮接口
	btn1 = new QPushButton("返回", customPlot);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	btn1->move(0, 0);
	btn1->resize(50, 25);
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsReturn()));

	//坐标轴字体颜色和底色设置
	customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
	customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
	customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
	customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
	customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
	customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
	customPlot->xAxis->setTickLabelColor(Qt::white);
	customPlot->yAxis->setTickLabelColor(Qt::white);
	QLinearGradient plotGradient;
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(0, 0, 0));
	plotGradient.setColorAt(1, QColor(0, 0, 0));
	customPlot->setBackground(plotGradient);
	setCentralWidget(customPlot);

	this->show();
}

void Kline::IsReturn()
{
	this->close();
}

int questKline()
{
	QUESTFILE3 client;
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
bool QUESTFILE3::InitSock()    //初始socket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long QUESTFILE3::ResolveAdress(char *serverIp)   //解析IP地址
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
SOCKET QUESTFILE3::ConnectServer(u_long serverIp, int port)   //连接服务器
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
bool QUESTFILE3::ProcessConnection(SOCKET sd)      //进行通信
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
bool QUESTFILE3::RecvCatalogInfo(SOCKET sd)   //接收目录信息
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
bool QUESTFILE3::SendDownLoadFileName(SOCKET sd)      //发送下载的文件名
{
	cout << "请输入你要下载的文件名" << endl;
	char fileName[_MAX_FNAME + _MAX_EXT] = "D:\\StockData\\test4.txt";
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
bool QUESTFILE3::ReceiveFileLength(SOCKET sd)     //接收下载的文件长度
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
bool QUESTFILE3::ReceiveFileName(SOCKET sd)   //接收下载的文件名
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
bool QUESTFILE3::ReceiveFile(SOCKET sd)      //接收文件内容
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
void QUESTFILE3::CloseSocket()   //关闭套接字
{
	closesocket(sd);
	WSACleanup();
}