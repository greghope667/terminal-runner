#pragma once

#include <QWidget>
#include <QMainWindow>

class Console;

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Console* console_;

public:
	explicit MainWindow();

public Q_SLOTS:
	void addEditor();
};

