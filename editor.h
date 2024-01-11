#pragma once

#include <QWidget>

class Console;

class Editor : public QWidget
{
	Q_OBJECT

public:
	explicit Editor(QWidget* parent = nullptr);

Q_SIGNALS:
	void sendText(const QString& cmd);
};
