#include "QtGuiApplication2.h"

int questmainmenu();
MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)  //��Ʊ�б�
{
	//���ڳ�ʼ������
	this->resize(1800, 800);
	this->setWindowTitle("��Ʊ�б�");
	this->setStyleSheet("background-color: rgb(0,0,0)");
	int columncount = 29;
	int rowcount = 2000;

	//����������ڴ����У���������
	QTableWidget * maintable = new QTableWidget(this);
	setCentralWidget(maintable);
	maintable->setRowCount(rowcount);
	maintable->setColumnCount(columncount);
	maintable->resize(1600, 800);
	maintable->horizontalHeader()->setMinimumSectionSize(45);
	maintable->horizontalHeader()->setMaximumSectionSize(45);
	maintable->resizeRowsToContents();
	maintable->verticalHeader()->setVisible(false);
	maintable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:black;font:8pt '����';color: white;}");
	maintable->setStyleSheet("color: white");
	maintable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	maintable->setSelectionBehavior(QAbstractItemView::SelectRows);
	maintable->setSelectionMode(QAbstractItemView::SingleSelection);
	maintable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	maintable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	maintable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	QStringList header;
	header << "��Ʊ"<<"��Ʊ����"<<"��Ʊ����"<<"�������̼�"<<"���ս����"<<"���ճֲ���"<<"��ͣ��"<<"��ͣ��"<<"�ܹɱ�"<<"��ͨ��"
		<<"��Լ��������"<<"��С�䶯��λ"<<"������"<<"������"<<"��Լ��RZRK�Ĵ���"<<"��Լ�ڽ������Ĵ���"<<"��Ϣ��"<<"��Ȩ��Ϣ"<<"ͣ��"<<"������"
		<<"�޼۵�����µ�������"<<"�޼۵���С�µ�������"<<"Ͷ�����ʵ��Թ������"<<"��С�ع�����"<<"���ع�����"<<"֤ȯ����" <<"֤ȯ��������Ը�λ"<<"֤ȯ��������Ե�λ"<<"ҪԼ�չ���Ϣ";
	maintable->setHorizontalHeaderLabels(header);//���ñ�ͷ

	//��������mainmenu�ļ���ϵͳ�����ļ�
	FILE* fp = fopen("D:/shixi/shili/StockSystem/QtGuiApplication2/test1.txt", "r");
	if (fp == NULL)
	{
		int quest = questmainmenu();
		if (quest == 0)
		{
			QMessageBox::information(this, tr("404��sorry"), tr("�ͻ�����������ʧ�ܣ�"));
		}
	}

	//���ļ������ж�ȡ�����ݴ��ڱ����
	QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test1.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404��sorry"), tr("���ݼ���ʧ�ܣ�"));
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
				item->setTextColor(QColor(Qt::red));       //���ø�������
			maintable->setItem(rowpresent, columnpresent, item);
		}
		rowpresent++;
		line = in.readLine();
	}
	
	//����һ�еĹ�Ʊ����һ����Ϊ��ť��������ʽ
	Mybtn *pBtn = new Mybtn(); 
	QStringList list = linepresent.split("\t");
	pBtn->setText(list[2]);
	pBtn->setStyleSheet("color: yellow");
	connect(pBtn, SIGNAL(doubleClicked()),this, SLOT(SlotSpecific()));
	maintable->setCellWidget(0, 2, pBtn);
	
	//ʹ�����Ը��ݴ��ڴ�С����
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
	connect(m->btn1, SIGNAL(clicked()), this, SLOT(SlotReshow()));//��һ�����ڷ���ʱ���źŽ��ղ�
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
bool QUESTFILE::InitSock()    //��ʼsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long QUESTFILE::ResolveAdress(char *serverIp)   //����IP��ַ
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
SOCKET QUESTFILE::ConnectServer(u_long serverIp, int port)   //���ӷ�����
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
bool QUESTFILE::ProcessConnection(SOCKET sd)      //����ͨ��
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
bool QUESTFILE::RecvCatalogInfo(SOCKET sd)   //����Ŀ¼��Ϣ
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
bool QUESTFILE::SendDownLoadFileName(SOCKET sd)      //�������ص��ļ���
{
	cout << "��������Ҫ���ص��ļ���" << endl;
	char fileName[_MAX_FNAME + _MAX_EXT] = "D:\\StockData\\test1.txt";
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
bool QUESTFILE::ReceiveFileLength(SOCKET sd)     //�������ص��ļ�����
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
bool QUESTFILE::ReceiveFileName(SOCKET sd)   //�������ص��ļ���
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
bool QUESTFILE::ReceiveFile(SOCKET sd)      //�����ļ�����
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
void QUESTFILE::CloseSocket()   //�ر��׽���
{
	closesocket(sd);
	WSACleanup();
}
