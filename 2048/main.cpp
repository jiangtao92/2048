#include "QtGuiApplication.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	srand(time(nullptr));
	QApplication a(argc, argv);
	QtGuiApplication w;
	w.show();
	return a.exec();
}
