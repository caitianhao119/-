#include "QtGuiApplication2.h"

int quest();  
ConditionMenu::ConditionMenu(QWidget *parent)
	: QMainWindow(parent)  //��Ʊ����
{
	this->setStyleSheet("background-color: rgb(0,0,0)");
	this->resize(1800, 800);
	//QCustomPlot���ڳ�ʼ������
	customPlot = new QCustomPlot(this);
	customPlot->resize(1800, 800);
	this->setWindowTitle("000001 ƽ������");
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables); //�����������
	customPlot->setStyleSheet("background-color: rgb(0,0,0)");

	//����ͼ�������������ݴ���
	QSharedPointer<QCPAxisTickerTime> tickertime(new QCPAxisTickerTime); //������Ϊʱ�䣬����С��λΪ��
	float hours = 9.5;
	tickertime->setTimeFormat("%h:%m:%s"); //�������ǩ��ʽ
	tickertime->setTickCount(30);
	tickertime->setTickOrigin(hours * 3600);
	customPlot->xAxis->setTicker(tickertime);
	customPlot->xAxis->setRange(hours*3600 , hours * 3600 + 3600*2);//�����귶Χ
	customPlot->xAxis->setTickLabelRotation(15);
	customPlot->xAxis->setBasePen(Qt::NoPen);//���غ�����
	customPlot->xAxis->setTickLabels(false);
	customPlot->xAxis->setTicks(false);
	QSharedPointer<QCPAxisTicker> tickertext (new QCPAxisTicker);
	tickertext->setTickCount(15);
	tickertext->setTickOrigin(16.35);
	customPlot->yAxis->setTicker(tickertext);
	customPlot->yAxis->setRange(16.20,16.50);//�����귶Χ

	//����ͼ�����������ǩ��ɫ�ͱ�����ɫ����
	customPlot->axisRect()->setBackground(QBrush(Qt::black));
	customPlot->xAxis->grid()->setPen(QPen(QColor(50, 50, 50)));
	customPlot->yAxis->grid()->setPen(QPen(QColor(50, 50, 50)));
	customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(50, 50, 50)));
	customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(50, 50, 50)));
	customPlot->xAxis->grid()->setSubGridVisible(true);
	customPlot->yAxis->grid()->setSubGridVisible(true);
	customPlot->xAxis->grid()->setZeroLinePen(QPen(Qt::white));
	customPlot->yAxis->grid()->setZeroLinePen(QPen(Qt::white));
	customPlot->yAxis->setTickLabelPadding(20);
	customPlot->yAxis->setTickLabelColor(Qt::red);

	//��״ͼ�������������ݴ�����ɫ���ã�ͬ�����ƣ�
	QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
	customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
	volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 200));
	volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
	volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
	customPlot->plotLayout()->setRowSpacing(0);
	volumeAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
	volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
	volumeAxisRect->axis(QCPAxis::atBottom)->setRange(hours * 3600, hours * 3600 + 3600 * 2);
	volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(tickertime);
	volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
	volumeAxisRect->axis(QCPAxis::atBottom)->setPadding(50);
	volumeAxisRect->axis(QCPAxis::atLeft)->setRange(0, 3500);
	volumeAxisRect->setBackground(QBrush(Qt::black));
	volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(50, 50, 50)));
	volumeAxisRect->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(50, 50, 50)));
	volumeAxisRect->axis(QCPAxis::atLeft)->setTickLabelPadding(20);
	volumeAxisRect->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::darkGreen);
	volumeAxisRect->axis(QCPAxis::atRight)->setTickLabelColor(Qt::darkGreen);
	volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::blue);

	//������ͼ����״ͼ��������һͬ���ţ��������ʹx�����
	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
	connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
	QCPMarginGroup *group = new QCPMarginGroup(customPlot);
	customPlot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, group);
	volumeAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, group);

	//����QCPBars�����洢��״ͼ����
	QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
	volumeNeg->setPen(QPen(Qt::yellow));
	
	//��������conditionmenu�ļ���ϵͳ�����ļ�
	FILE* fp = fopen("D:/shixi/shili/StockSystem/QtGuiApplication2/test3.txt", "r");
	if (fp == NULL)
	{
		int questcondotion = quest();
		if (questcondotion == 0)
		{
			QMessageBox::information(this, tr("404��sorry"), tr("�ͻ�����������ʧ�ܣ�"));
		}
	}
	
	//���ļ������ж�ȡ���������ݴ���
	QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test3.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404��sorry"), tr("���ݼ���ʧ�ܣ�"));
	}
	QTextStream in(&file);
	QString line = in.readLine();
	QStringList list = line.split("\t");
	float firstsummoney = list[2].toFloat();
	float firstsumnum = list[3].toFloat();
	float agosumnum = firstsumnum;        //��ȡ��һ��ʱ�̵ĳɽ����ͳɽ��ܼ�
	QVector<double> yData1,yData2,xData;//���������洢����ͼ����
	while (!line.isNull())
	{
		QStringList list = line.split("\t");
		QDateTime thistime;
		thistime = QDateTime::fromString(list[0], "yyyy-MM-ddhh:mm:ss");
		int thissed = thistime.time().second();
		int thismin = thistime.time().minute();
		int thishour = thistime.time().hour();
		int sumtime = thishour * 3600 + thismin * 60 + thissed;
		xData.push_back(sumtime);
		float newnum = list[1].toFloat();
		yData1.push_back(newnum);
		float nowsummoney = list[2].toFloat();
		float nowsumnum = list[3].toFloat();
		float  nowpercent =  (nowsummoney - firstsummoney)/((nowsumnum - firstsumnum)*100);
		yData2.push_back(nowpercent);
		volumeNeg->addData(sumtime, nowsumnum - agosumnum); //һ�������Ʒ�ʱ�ɽ�������
		agosumnum = nowsumnum;
		line = in.readLine();
	}
	
	customPlot->addGraph();
	customPlot->graph()->setBrush(QColor(209,233,233,60));
	customPlot->graph()->setPen(QPen(Qt::red));      
	customPlot->graph()->setData(xData, yData1);    //����ʵʱ�ɽ�������ͼ
	customPlot->addGraph();
	customPlot->graph()->setPen(QPen(Qt::yellow));
	customPlot->graph()->setData(xData, yData2);  //�����վ�������ͼ
	
	//�����������������
	customPlot->yAxis2->setVisible(true);
	customPlot->yAxis2->setRange(0.0100,-0.0100);
	customPlot->yAxis2->setNumberFormat("%d");
	volumeAxisRect->axis(QCPAxis::atRight)->setVisible(true);
	volumeAxisRect->axis(QCPAxis::atRight)->setRange(0, 3500);
	
	//���ð�ť������һ�����ڼ�������һ������
	btn1 = new QPushButton("����", customPlot);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	btn1->move(0,0);
	btn1->resize(50, 25);
	QPushButton *btn2 = new QPushButton("K��", customPlot);
	btn2->setStyleSheet("background-color: rgb(187,255,255)");
	btn2->move(100,0);
	btn2->resize(50, 25);
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsReturn()));
	connect(btn2, SIGNAL(clicked()), this, SLOT(IsK()));

	//���������ɫ����
	QLinearGradient plotGradient;
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(0, 0, 0));
	plotGradient.setColorAt(1, QColor(0, 0, 0));
	customPlot->setBackground(plotGradient);
	setCentralWidget(customPlot);

	this->show();

}

void ConditionMenu::IsK()
{
	this->hide();
	m = new Kline;
	connect(m->btn1, SIGNAL(clicked()), this, SLOT(SlotReshow()));
}

void ConditionMenu::SlotReshow()
{
	this->show();
}

void ConditionMenu::IsReturn()
{
	this->hide();
}

int quest()
{
	QUESTFILE2 client;
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
bool QUESTFILE2::InitSock()    //��ʼsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long QUESTFILE2::ResolveAdress(char *serverIp)   //����IP��ַ
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
SOCKET QUESTFILE2::ConnectServer(u_long serverIp, int port)   //���ӷ�����
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
bool QUESTFILE2::ProcessConnection(SOCKET sd)      //����ͨ��
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
bool QUESTFILE2::RecvCatalogInfo(SOCKET sd)   //����Ŀ¼��Ϣ
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
bool QUESTFILE2::SendDownLoadFileName(SOCKET sd)      //�������ص��ļ���
{
	cout << "��������Ҫ���ص��ļ���" << endl;
	char fileName[_MAX_FNAME + _MAX_EXT] = "D:\\StockData\\test3.txt";
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
bool QUESTFILE2::ReceiveFileLength(SOCKET sd)     //�������ص��ļ�����
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
bool QUESTFILE2::ReceiveFileName(SOCKET sd)   //�������ص��ļ���
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
bool QUESTFILE2::ReceiveFile(SOCKET sd)      //�����ļ�����
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
void QUESTFILE2::CloseSocket()   //�ر��׽���
{
	closesocket(sd);
	WSACleanup();
}