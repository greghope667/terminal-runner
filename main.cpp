#include "main.h"

#include "window.h"

#include <QApplication>
#include <QMessageBox>
#include <iostream>

void fatal(QWidget* w, const QString& message)
{
	std::cerr << "Fatal error: " << message.toStdString() << std::endl;
	QMessageBox::critical(w, "Error", message);
	QApplication::exit(EXIT_FAILURE);
	_Exit(EXIT_FAILURE); // definitely exit
}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	return app.exec();
}
