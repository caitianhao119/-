#include "QtGuiApplication2.h"

int questKline();
Kline::Kline(QWidget *parent)
	: QMainWindow(parent) //k�ߴ���
{
	//�������ݸ�ʽ��ʼ�� 
	this->resize(1800, 800);
	this->setWindowTitle("000001 ƽ������");

	//k�ߴ���QCustomPlot�������������ݴ���
	QCustomPlot *customPlot = new QCustomPlot(this);
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	QDateTime start = QDateTime(QDate(2019,1,1)); //��ʼʱ��
	QDateTime end = QDateTime(QDate(2019,12,31));  //ĩʱ��
	double startTime = start.toTime_t();
	double endTime = end.toTime_t();
	double binSize = 3600 * 24;  //��kͼ��һ��һ��
	QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
	dateTimeTicker->setDateTimeSpec(Qt::UTC);
	dateTimeTicker->setDateTimeFormat("yyyy-M-d"); //����ʱ���ʽ
	dateTimeTicker->setTickCount(30); 
	customPlot->xAxis->setTicker(dateTimeTicker);
	customPlot->xAxis->setTickLabelRotation(15);
	customPlot->xAxis->setRange(startTime,endTime);
	QSharedPointer<QCPAxisTicker> tickertext(new QCPAxisTicker);
	tickertext->setTickCount(15);
	customPlot->yAxis->setTicker(tickertext);
	customPlot->yAxis->setRange(5.00, 25.00);  //y�᷶Χ

	//��������kline�ļ���ϵͳ�����ļ�
	FILE* fp = fopen("D:/shixi/shili/StockSystem/QtGuiApplication2/test4.txt", "r");
	if (fp == NULL)
	{
		int quest = questKline();
		if (quest == 0)
		{
			QMessageBox::information(this, tr("404��sorry"), tr("�ͻ�����������ʧ�ܣ�"));
		}
	}

	//���ļ�׼�����л���
	QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test4.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404��sorry"), tr("���ݼ���ʧ�ܣ�"));
	}
	QTextStream in(&file);
	QString line = in.readLine();
	QStringList list = line.split("\t");

	//���д������ݣ�����2019һ�������kͼ��
	//�������洢ÿ��ʱ�̵�ʱ��͹�Ʊ�۸�
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

	//��QCustomPlot�Դ�����ͺ�������k�߻���
	QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
	candlesticks->setName("Candlestick");
	candlesticks->setChartStyle(QCPFinancial::csCandlestick);
	candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
	candlesticks->setWidth(binSize*0.9);  //ÿ��k�߸���
	candlesticks->setTwoColored(true);
	candlesticks->setBrushPositive(QColor(Qt::red));
	candlesticks->setBrushNegative(QColor(Qt::green));
	candlesticks->setPenPositive(QPen(QColor(Qt::red)));
	candlesticks->setPenNegative(QPen(QColor(Qt::green)));
	setCentralWidget(customPlot);

	//������һ�㴰�ڰ�ť�ӿ�
	btn1 = new QPushButton("����", customPlot);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	btn1->move(0, 0);
	btn1->resize(50, 25);
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsReturn()));

	//������������ɫ�͵�ɫ����
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
		//cout << "��ʼsocketʧ��" << endl;
		return 0;
	}
	SOCKET saRemote = client.ConnectServer(client.ResolveAdress(SERVER_IP), PORT);
	if (saRemote == INVALID_SOCKET)
	{
		//cout << "���ӷ�����ʧ��" << endl;
		return 0;
	}
	if (!client.ProcessConnection(saRemote))
	{
		return 0;
	}
	client.CloseSocket();
	return 1;
}
bool QUESTFILE3::InitSock()    //��ʼsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long QUESTFILE3::ResolveAdress(char *serverIp)   //����IP��ַ
{
	u_long nAddr = inet_addr(serverIp);
	if (nAddr == INADDR_NONE)  //����serverIpʹ�õ�����������ʽ
	{
		hostent *ent = gethostbyname(serverIp);
		if (ent == NULL)
		{
			cout << "��ȡ����������" << WSAGetLastError() << endl;
		}
		else
		{
			nAddr = *((u_long *)ent->h_addr_list[0]);
		}
	}
	if (nAddr == INADDR_NONE)
	{
		cout << "����������ַʧ��" << endl;
	}
	return nAddr;
}
SOCKET QUESTFILE3::ConnectServer(u_long serverIp, int port)   //���ӷ�����
{
	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == INVALID_SOCKET)
	{
		cout << "�����׽���ʧ��" << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = serverIp;
	saServer.sin_port = htons(port);
	if (connect(sd, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "���ӷ�����ʧ��" << WSAGetLastError() << endl;
		closesocket(sd);
		return INVALID_SOCKET;
	}
	return sd;
}
bool QUESTFILE3::ProcessConnection(SOCKET sd)      //����ͨ��
{
	//ϵͳ������
	int nRecvBuf = 2048000;//����Ϊ2000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//���ͻ�����
	int nSendBuf = 2048000;//����Ϊ2000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	Message::MsgDownLoadFile msgDownLoadFile;
	if (send(sd, (char *)&msgDownLoadFile, sizeof(Message::MsgDownLoadFile), 0) == SOCKET_ERROR)
	{
		cout << "���������ļ���Ϣʧ��" << WSAGetLastError() << endl;
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
bool QUESTFILE3::RecvCatalogInfo(SOCKET sd)   //����Ŀ¼��Ϣ
{
	int flag = 1;     //����Ŀ¼��Ϣ�ɹ���־
	char buff[MAX_PACK_SIZE];
	Message::MsgHead *msgHead;
	while (true)
	{
		if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
		{
			cout << "����Ŀ¼��Ϣʧ��" << WSAGetLastError() << endl;
			flag = 0;
			break;
		}
		msgHead = (Message::MsgHead *)buff;
		if (msgHead->msgId == MSG_COMPLETE)      //�ж���Ϣ�Ƿ��Ǳ�׼��Ϣ
		{
			cout << "Ŀ¼��Ϣ�������" << endl;
			break;
		}
		else
		{
			cout << buff << endl;     //����������Ŀ¼��Ϣ�����ļ���
		}
	}
	if (flag == 0)
	{
		return false;
	}
	return true;
}
bool QUESTFILE3::SendDownLoadFileName(SOCKET sd)      //�������ص��ļ���
{
	cout << "��������Ҫ���ص��ļ���" << endl;
	char fileName[_MAX_FNAME + _MAX_EXT] = "D:\\StockData\\test4.txt";
	Message::MsgFileName msgFileName;
	strcpy(msgFileName.fileName, fileName);
	if (send(sd, (char *)&msgFileName, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "���������ļ�������" << WSAGetLastError() << endl;
		system("pause");
		return false;
	}
	return true;
}
bool QUESTFILE3::ReceiveFileLength(SOCKET sd)     //�������ص��ļ�����
{
	Sleep(100);
	char buff[MAX_PACK_SIZE];
	Message::MsgFileLength *msgFileLength;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "�����ļ�����ʧ��" << WSAGetLastError() << endl;
		return false;
	}
	msgFileLength = (Message::MsgFileLength *)buff;
	nFileLength = msgFileLength->fileLength;
	cout << "���յ��ļ�����" << nFileLength << endl;

	return true;
}
bool QUESTFILE3::ReceiveFileName(SOCKET sd)   //�������ص��ļ���
{
	Sleep(100);
	char buff[MAX_PACK_SIZE];
	memset(fileName, 0, sizeof(char)*(_MAX_FNAME + _MAX_EXT));
	Message::MsgFileName *msgFileName;
	if (recv(sd, buff, MAX_PACK_SIZE, 0) == SOCKET_ERROR)
	{
		cout << "�����ļ�������" << endl;
		return false;
	}
	msgFileName = (Message::MsgFileName *)buff;
	strcpy(fileName, msgFileName->fileName);
	cout << "���յ��ļ���" << fileName << endl;
	return true;
}
bool QUESTFILE3::ReceiveFile(SOCKET sd)      //�����ļ�����
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
void QUESTFILE3::CloseSocket()   //�ر��׽���
{
	closesocket(sd);
	WSACleanup();
}