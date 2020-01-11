#include "QtGuiApplication2.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <string>
#pragma execution_character_set("utf-8")
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginMainWindow w;
	return a.exec();
}