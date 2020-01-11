#include "QtGuiApplication2.h"

LoginMainWindow::LoginMainWindow(QWidget *parent)
	: QMainWindow(parent)//登陆窗口 
{
	//初始化窗口 
	widegt = new QWidget(this);
	this->setMaximumSize(500, 350);
	this->setMinimumSize(500, 350);
	this->setWindowTitle("重庆睿智融科");
	widegt->setMaximumSize(500, 350);
	widegt->setMinimumSize(500, 350);
	widegt->setStyleSheet("background-color: rgb(255,255,255)"); 

	//添加标签图片
	QLabel *labtoplogo = new QLabel(widegt);
	labtoplogo->setFixedHeight(100);
	QImage *logo = new QImage;
	int i=logo->load("D:/shixi/shili/QtGuiApplication2/QtGuiApplication2/Resources/lab/logo1.png");
	if (i==0)
		QMessageBox::information(widegt, tr("404，sorry"), tr("图片加载失败！"));
	labtoplogo->setPixmap(QPixmap::fromImage(logo->scaled(160, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	QLabel *labetitle = new QLabel(widegt);
	labetitle->setText("迅投股票系统");
	//设置标签字体
	QFont font1;
	font1.setPointSize(20);
	font1.setBold(true);
	font1.setFamily("KaiTi");
	labetitle->setFont(font1);
	labetitle->setFixedHeight(100);
	//设置水平布局器将标签和图片结合 
	QHBoxLayout *hlayouttoptitel = new QHBoxLayout();
	hlayouttoptitel->addWidget(labtoplogo);
	hlayouttoptitel->addWidget(labetitle);

	//设置账号密码输入框
	QLabel *label = new QLabel(widegt);
	label->setText("账号");
	QLabel *labe2 = new QLabel(widegt);
	labe2->setText("密码");
	label->setFixedSize(35, 25);
	labe2->setFixedSize(35, 25);

	lineEdit1 = new QLineEdit(widegt);
	lineEdit1->setEchoMode(QLineEdit::Normal);
	lineEdit1->setClearButtonEnabled(true);
	lineEdit1->setPlaceholderText("请输入你的账号");
	lineEdit2 = new QLineEdit(widegt);
	lineEdit2->setEchoMode(QLineEdit::Password);
	lineEdit2->setPlaceholderText("请输入你的密码");
	lineEdit2->setClearButtonEnabled(true);
	lineEdit1->setFixedSize(170, 25);
	lineEdit2->setFixedSize(170, 25);

	//用水平布局器将标签和文本框结合
	QHBoxLayout *hlayout1 = new QHBoxLayout();
	hlayout1->addStretch(2);
	hlayout1->addWidget(label);
	hlayout1->addWidget(lineEdit1);
	hlayout1->addStretch(2);
	QHBoxLayout *hlayout2 = new QHBoxLayout(); 
	hlayout2->addStretch(2);
	hlayout2->addWidget(labe2);
	hlayout2->addWidget(lineEdit2);
	hlayout2->addStretch(2);

	//设置按钮及其字体，用水平布局器配置
	QPushButton *btn1 = new QPushButton("登陆", widegt);
	QPushButton *btn2 = new QPushButton("注册", widegt);
	QPushButton *btn3 = new QPushButton("找回密码", widegt);
	QFont font2;
	font2.setPointSize(13);
	font2.setBold(true);
	btn1->setFont(font2);
	btn1->setFixedSize(250, 50);
	btn2->setFixedSize(100, 25);
	btn3->setFixedSize(100, 25);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	QHBoxLayout *hlayout3 = new QHBoxLayout();
	hlayout3->addStretch();
	hlayout3->addWidget(btn1);
	hlayout3->addStretch();
	QHBoxLayout *hlayout4 = new QHBoxLayout();
	hlayout4->addStretch();
	hlayout4->addWidget(btn2);
	hlayout4->addWidget(btn3);
	hlayout4->addStretch();

	//设置槽函数
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsLogin()));   
	connect(btn2, SIGNAL(clicked()), this, SLOT(IsRegister()));
	connect(lineEdit2, SIGNAL(returnPressed()), this, SLOT(IsLogin()));

	//整个窗口布置垂直布局器
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(hlayouttoptitel);
	layout->addLayout(hlayout1);
	layout->addLayout(hlayout2);
	layout->addLayout(hlayout3);
	layout->addLayout(hlayout4);
	widegt->setLayout(layout); 
	layout->setSpacing(0);

	this->show();

}

int Login(string s1, string s2);
void LoginMainWindow::IsLogin()
{
	QString s1 = lineEdit1->text();
	QString s2 = lineEdit2->text();
	if (s1==NULL || s2==NULL)
		QMessageBox::information(widegt, tr("error"), tr("请输入账号密码后登陆"));
	else
	{
		int loginreturn = Login(s1.toStdString(), s2.toStdString());
		if (loginreturn == 1)
		{
			this->close();
			m = new MainMenu;
		}
		else
		{
			QMessageBox::information(widegt, tr("error"), tr("请输入正确账号及密码"));
		}
	}
	
}

void LoginMainWindow::IsRegister()
{
	QMessageBox::information(widegt, tr("sorry"), tr("内容正在完善"));
}


int Login(string s1, string s2)
{
	Client client;
	if (!client.InitSock())
	{
		cout << "初始socket失败" << endl;
		return 0;
	}
	SOCKET saRemote = client.ConnectServer(client.ResolveAdress(SERVER_IP), PORT);
	if (saRemote == INVALID_SOCKET)
	{
		cout << "连接服务器失败" << endl;
		return 0;
	}
	if (!client.ProcessConnection(saRemote, s1.c_str(), s2.c_str()))
	{
		return 0;
	}
	client.CloseSocket();
	return 1;
}
bool Client::InitSock()    //初始socket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
u_long Client::ResolveAdress(char *serverIp)   //解析IP地址
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
SOCKET Client::ConnectServer(u_long serverIp, int port)   //连接服务器
{
	sd = socket(AF_INET, SOCK_STREAM, 0);
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
bool Client::ProcessConnection(SOCKET sd, const char acc[], const char pass[])      //进行通信
{
	//系统缓冲区
	int nRecvBuf = 2048000;//设置为2000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//发送缓冲区
	int nSendBuf = 2048000;//设置为2000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

	//向服务器发送用户名与密码
	Message::MsgLogin msglogin;
	if (send(sd, (char *)&msglogin, sizeof(Message::MsgLogin), 0) == SOCKET_ERROR)
	{
		cout << "发送消息失败" << endl;
		return false;
	}
	Sleep(100);     //睡眠100ms保证对方将发送的消息取走

	if (!SendAccountAndPass(sd, acc, pass))//发送用户名
	{
		cout << "发送用户名失败" << endl;
		return false;
	}
	Sleep(100);

	char buff[1025];
	int num = 0;
	num = recv(sd, buff, 1024, 0);
	if (num > 0)
	{
		string cmp;
		buff[num] = '\0';
		cmp = buff;
		if (cmp == "TRUE")
		{
			//cout << "right" << endl;
			return 1;
		}
		else 
		{
			//cout << "false" << endl;
			return 0;
		}

	}
	return true;
}

bool Client::SendAccountAndPass(SOCKET sd, const char acc[], const char pass[])
{
	Message::MsgAccPass msgacc;
	string account = acc;
	string password = pass;
	account.append("*");
	account += password;
	cout << account << endl;
	if (send(sd, (char*)&msgacc, sizeof(Message::MsgAccPass), 0) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		send(sd, account.c_str(), strlen(account.c_str()), 0);
	}
	return true;
}


void Client::CloseSocket()   //关闭套接字
{
	closesocket(sd);
	WSACleanup();
}

//QMessageBox::information(NULL, s1, s2,
	//QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);