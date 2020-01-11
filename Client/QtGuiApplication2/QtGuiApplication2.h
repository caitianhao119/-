#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Clientlogin.h"
#include "questfile.h"
#include "questfile2.h"
#include "questfile3.h"
#include "windows.h"
#include <vector>
#include "string"
#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication2.h"
#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QDialog>
#include "QSlider.h"
#include "QString.h"
#include "qcustomplot.h"
#include "message.h"

#include "qcustomplot.h"
#pragma execution_character_set("utf-8")
#include <iostream>
using namespace std;


class Kline : public QMainWindow
{
	Q_OBJECT

public:
	Kline(QWidget *parent = Q_NULLPTR);
	QPushButton *btn1;
signals:

public slots:
	void IsReturn();
};

class ConditionMenu : public QMainWindow
{
	Q_OBJECT

public:
	ConditionMenu(QWidget *parent = Q_NULLPTR);
	QCustomPlot *customPlot;
	QPushButton *btn1;
	Kline *m;
signals:

public slots:
	void IsReturn();
	void IsK();
	void SlotReshow();
};


class MainMenu : public QMainWindow
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);
	ConditionMenu *m;

signals:

public slots:
	void SlotSpecific();
	void SlotReshow();
};
 

class LoginMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginMainWindow(QWidget *parent = Q_NULLPTR);
	QWidget *widegt;
	QLineEdit *lineEdit1;
	QLineEdit *lineEdit2;
	MainMenu *m;
signals:

public slots :
	void IsLogin();
	void IsRegister();
};

class MyQCPFinancial :public QCPFinancial
{
	Q_OBJECT
public:
	explicit MyQCPFinancial(QCPAxis *keyAxis, QCPAxis *valueAxis) :QCPFinancial(keyAxis, valueAxis) {}
	static QCPFinancialDataContainer mydate(const QVector<double> &time, const QVector<double> &value1, const QVector<double> &value2, const QVector<double> &value3, const QVector<double> &value4, double timeBinSize, double timeBinOffset = 0)
	{
		QCPFinancialDataContainer data;
		QCPFinancialData currentBinData(0, value1.first(), value2.first(), value3.first(), value4.first());
		data.add(currentBinData);
		return data;
	}

};


class Mybtn :public QPushButton
{
	Q_OBJECT
public:
	explicit Mybtn(QWidget *parent = 0) :QPushButton(parent) {}
	virtual void mouseDoubleClickEvent(QMouseEvent *event) {
		if (event->button() == Qt::LeftButton) {
			emit doubleClicked();
		}
	}
signals:
	void doubleClicked();
};
