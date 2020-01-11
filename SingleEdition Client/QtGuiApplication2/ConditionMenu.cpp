#include "QtGuiApplication2.h"

ConditionMenu::ConditionMenu(QWidget *parent)
	: QMainWindow(parent)
{
	this->setStyleSheet("background-color: rgb(0,0,0)");
	this->resize(1800, 800);
	customPlot = new QCustomPlot(this);
	customPlot->resize(1800, 800);
	this->setWindowTitle("000001 平安银行");
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	customPlot->setStyleSheet("background-color: rgb(0,0,0)");

	QSharedPointer<QCPAxisTickerTime> tickertime(new QCPAxisTickerTime);
	float hours = 9.5;
	tickertime->setTimeFormat("%h:%m:%s");
	tickertime->setTickCount(30);
	tickertime->setTickOrigin(hours * 3600);
	customPlot->xAxis->setTicker(tickertime);
	customPlot->xAxis->setRange(hours*3600 , hours * 3600 + 3600*2);
	customPlot->xAxis->setTickLabelRotation(15);
	customPlot->xAxis->setBasePen(Qt::NoPen);
	customPlot->xAxis->setTickLabels(false);
	customPlot->xAxis->setTicks(false);
	
	QSharedPointer<QCPAxisTicker> tickertext (new QCPAxisTicker);
	tickertext->setTickCount(15);
	tickertext->setTickOrigin(16.35);
	customPlot->yAxis->setTicker(tickertext);
	customPlot->yAxis->setRange(16.20,16.50);


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

	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
	connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
	QCPMarginGroup *group = new QCPMarginGroup(customPlot);
	customPlot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, group);
	volumeAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, group);

	QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
	volumeNeg->setPen(QPen(Qt::yellow));
	QVector<double> yData1,yData2,xData;
	QFile file("D:/shixi/shili/QtGuiApplication2/QtGuiApplication2/Resources/test3.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404，sorry"), tr("数据加载失败！"));
	}

	QTextStream in(&file);
	QString line = in.readLine();
	QStringList list = line.split("\t");
	float firstsummoney = list[2].toFloat();
	float firstsumnum = list[3].toFloat();
	float agosumnum = firstsumnum;
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
		qDebug() << nowpercent;
		volumeNeg->addData(sumtime, nowsumnum - agosumnum);
		agosumnum = nowsumnum;
		line = in.readLine();
	}
	
	customPlot->addGraph();
	customPlot->graph()->setBrush(QColor(209,233,233,60));
	customPlot->graph()->setPen(QPen(Qt::red));
	customPlot->graph()->setData(xData, yData1);
	customPlot->addGraph();
	customPlot->graph()->setPen(QPen(Qt::yellow));
	customPlot->graph()->setData(xData, yData2);
	
	
	customPlot->yAxis2->setVisible(true);
	customPlot->yAxis2->setRange(0.0100,-0.0100);
	customPlot->yAxis2->setNumberFormat("%d");
	volumeAxisRect->axis(QCPAxis::atRight)->setVisible(true);
	volumeAxisRect->axis(QCPAxis::atRight)->setRange(0, 3500);
	
	btn1 = new QPushButton("返回", customPlot);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	btn1->move(0,0);
	btn1->resize(50, 25);
	QPushButton *btn2 = new QPushButton("K线", customPlot);
	btn2->setStyleSheet("background-color: rgb(187,255,255)");
	btn2->move(100,0);
	btn2->resize(50, 25);
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsReturn()));
	connect(btn2, SIGNAL(clicked()), this, SLOT(IsK()));
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