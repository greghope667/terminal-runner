#pragma once

#include <QWidget>

namespace KParts { class ReadOnlyPart; }

class Console : public QWidget
{
	Q_OBJECT

private:
	KParts::ReadOnlyPart* part_ = nullptr;
	void load();

private Q_SLOTS:
	void closed();

public:
	explicit Console(QWidget* parent = nullptr);
	~Console();

public Q_SLOTS:
	void write(const QString& text);
	void interrupt();
};
