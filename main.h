#pragma once

#include <QMainWindow>
#include "console.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	Console* console_;

public:
	MainWindow();
};

[[noreturn]] void fatal(QWidget*, const QString& message);
