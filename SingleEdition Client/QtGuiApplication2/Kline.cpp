#include "QtGuiApplication2.h"


Kline::Kline(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(1800, 800);
	this->setWindowTitle("000001 平安银行");
	QCustomPlot *customPlot = new QCustomPlot(this);
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	QDateTime start = QDateTime(QDate(2019,1,1));
	QDateTime end = QDateTime(QDate(2019,12,31));
	//start.setTimeSpec(Qt::UTC);
	double startTime = start.toTime_t();
	double endTime = end.toTime_t();
	double binSize = 3600 * 24;
	QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
	dateTimeTicker->setDateTimeSpec(Qt::UTC);
	dateTimeTicker->setDateTimeFormat("yyyy-M-d");
	dateTimeTicker->setTickCount(30);
	customPlot->xAxis->setTicker(dateTimeTicker);
	customPlot->xAxis->setTickLabelRotation(15);
	customPlot->xAxis->setRange(startTime,endTime);
	QSharedPointer<QCPAxisTicker> tickertext(new QCPAxisTicker);
	tickertext->setTickCount(15);
	customPlot->yAxis->setTicker(tickertext);
	customPlot->yAxis->setRange(5.00, 25.00);

	QVector<double> time,value1;
	QFile file("D:/shixi/shili/QtGuiApplication2/QtGuiApplication2/Resources/test4.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("404，sorry"), tr("数据加载失败！"));
	}
	QTextStream in(&file);
	QString line = in.readLine();
	QStringList list = line.split("\t");
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

	QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
	candlesticks->setName("Candlestick");
	candlesticks->setChartStyle(QCPFinancial::csCandlestick);
	candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
	candlesticks->setWidth(binSize*0.9);
	candlesticks->setTwoColored(true);
	candlesticks->setBrushPositive(QColor(Qt::red));
	candlesticks->setBrushNegative(QColor(Qt::green));
	candlesticks->setPenPositive(QPen(QColor(Qt::red)));
	candlesticks->setPenNegative(QPen(QColor(Qt::green)));
	setCentralWidget(customPlot);

	btn1 = new QPushButton("返回", customPlot);
	btn1->setStyleSheet("background-color: rgb(187,255,255)");
	btn1->move(0, 0);
	btn1->resize(50, 25);
	connect(btn1, SIGNAL(clicked()), this, SLOT(IsReturn()));

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