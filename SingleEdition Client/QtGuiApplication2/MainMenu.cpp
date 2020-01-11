#include "QtGuiApplication2.h"


MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(1800, 800);
	this->setWindowTitle("��Ʊ�б�");
	this->setStyleSheet("background-color: rgb(0,0,0)");
	int columncount = 29;
	int rowcount = 2000;
	QTableWidget * maintable = new QTableWidget(this);
	setCentralWidget(maintable);
	maintable->setRowCount(rowcount);
	maintable->setColumnCount(columncount);
	maintable->resize(1600, 800);
	maintable->horizontalHeader()->setMinimumSectionSize(45);
	maintable->horizontalHeader()->setMaximumSectionSize(45);
	maintable->setShowGrid(true);
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
	maintable->setHorizontalHeaderLabels(header);
	//QFile file("D:/shixi/shili/StockSystem/QtGuiApplication2/test1.txt");
	QFile file("D:/shixi/shili/QtGuiApplication2/QtGuiApplication2/Resources/test1.txt");
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
				item->setTextColor(QColor(128,255,255));
			if (columnpresent == 2)
				item->setTextColor(QColor(Qt::yellow));
			if (columnpresent == 3)
				item->setTextColor(QColor(200, 111, 100));
			if (columnpresent == 6)
				item->setTextColor(QColor(Qt::red));
			if (columnpresent == 7)
				item->setTextColor(QColor(Qt::green));
			if (columnpresent == 12)
				item->setTextColor(QColor(Qt::red));
			maintable->setItem(rowpresent, columnpresent, item);
		}
		rowpresent++;
		line = in.readLine();
	}

	Mybtn *pBtn = new Mybtn();
	QStringList list = linepresent.split("\t");
	pBtn->setText(list[2]);
	pBtn->setStyleSheet("color: yellow");
	connect(pBtn, SIGNAL(doubleClicked()),this, SLOT(SlotSpecific()));
	maintable->setCellWidget(0, 2, pBtn);
	
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
	connect(m->btn1, SIGNAL(clicked()), this, SLOT(SlotReshow()));
}

void MainMenu::SlotReshow()
{
	this->show();
}
