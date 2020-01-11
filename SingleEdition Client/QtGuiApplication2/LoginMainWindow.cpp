#include "QtGuiApplication2.h"


LoginMainWindow::LoginMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	widegt = new QWidget(this);
	this->setMaximumSize(500, 350);
	this->setMinimumSize(500, 350);
	this->setWindowTitle("��������ڿ�");
	widegt->setMaximumSize(500, 350);
	widegt->setMinimumSize(500, 350);
	widegt->setStyleSheet("background-color: rgb(255,255,255)");

	QLabel *labtoplogo = new QLabel(widegt);
	labtoplogo->setFixedHeight(100);
	QImage *logo = new QImage;
	int i=logo->load("D:/shixi/shili/QtGuiApplication2/QtGuiApplication2/Resources/lab/logo1.png");
	if (i==0)
		QMessageBox::information(widegt, tr("404��sorry"), tr("ͼƬ����ʧ�ܣ�"));
	labtoplogo->setPixmap(QPixmap::fromImage(logo->scaled(160, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	QLabel *labetitle = new QLabel(widegt);
	labetitle->setText("ѸͶ��Ʊϵͳ");
	QFont font1;
	font1.setPointSize(20);
	font1.setBold(true);
	font1.setFamily("KaiTi");
	labetitle->setFont(font1);
	labetitle->setFixedHeight(100);
	QHBoxLayout *hlayouttoptitel = new QHBoxLayout();
	hlayouttoptitel->addWidget(labtoplogo);
	hlayouttoptitel->addWidget(labetitle);

	QLabel *label = new QLabel(widegt);
	label->setText("�˺�");
	QLabel *labe2 = new QLabel(widegt);
	labe2->setText("����");
	label->setFixedSize(35, 25);
	labe2->setFixedSize(35, 25);

	lineEdit1 = new QLineEdit(widegt);
	lineEdit1->setEchoMode(QLineEdit::Normal);
	lineEdit1->setClearButtonEnabled(true);
	lineEdit1->setPlaceholderText("����������˺�");
	lineEdit2 = new QLineEdit(widegt);
	lineEdit2->setEchoMode(QLineEdit::Password);
	lineEdit2->setPlaceholderText("�������������");
	lineEdit2->setClearButtonEnabled(true);
	lineEdit1->setFixedSize(170, 25);
	lineEdit2->setFixedSize(170, 25);

	QHBoxLayout *hlayout1 = new QHBoxLayout();
	hlayout1->addStretch(2);
	hlayout1->addWidget(label);
	hlayout1->addWidget(lineEdit1);
	hlayout1->addStretch(2);

	QHBoxLayout *hlayout2 = new QHBoxLayout(); //ˮƽ������
	hlayout2->addStretch(2);
	hlayout2->addWidget(labe2);
	hlayout2->addWidget(lineEdit2);
	hlayout2->addStretch(2);

	QPushButton *btn1 = new QPushButton("��½", widegt);
	QPushButton *btn2 = new QPushButton("ע��", widegt);
	QPushButton *btn3 = new QPushButton("�һ�����", widegt);

	QFont font2;
	font2.setPointSize(13);
	font2.setBold(true);
	btn1->setFont(font2);

	btn1->setFixedSize(250, 50);
	btn2->setFixedSize(100, 25);
	btn3->setFixedSize(100, 25);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	//btn2->setFlat(true);
	//btn3->setFlat(true);
	//btn1->setWindowOpacity(0);


	QHBoxLayout *hlayout3 = new QHBoxLayout();
	hlayout3->addStretch();
	hlayout3->addWidget(btn1);
	hlayout3->addStretch();

	QHBoxLayout *hlayout4 = new QHBoxLayout();
	hlayout4->addStretch();
	hlayout4->addWidget(btn2);
	hlayout4->addWidget(btn3);
	hlayout4->addStretch();

	connect(btn1, SIGNAL(clicked()), this, SLOT(IsLogin()));    // �ź����
	connect(btn2, SIGNAL(clicked()), this, SLOT(IsRegister()));
	connect(lineEdit2, SIGNAL(returnPressed()), this, SLOT(IsLogin()));

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

void LoginMainWindow::IsLogin()
{
	QString s1 = lineEdit1->text();
	QString s2 = lineEdit2->text();
	if (s1==NULL || s2==NULL)
		QMessageBox::information(widegt, tr("error"), tr("�������˺�������½"));
	else
	{
		if (s1 == "1" && s2 == "1")
		{
			this->close();

			m = new MainMenu;
		}
		else
		{
			QMessageBox::information(widegt, tr("error"), tr("��������ȷ�˺ż�����"));
		}
	}
	
}

void LoginMainWindow::IsRegister()
{
	QMessageBox::information(widegt, tr("hello"), tr("Hello World!"));
}

//QMessageBox::information(NULL, s1, s2,
	//QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);