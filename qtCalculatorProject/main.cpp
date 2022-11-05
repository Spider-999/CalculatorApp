#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow calculator;
	calculator.show();

	return app.exec();
}
