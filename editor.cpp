#include "editor.h"

#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>

Editor::Editor(QWidget* parent)
	: QWidget(parent)
{
	setLayout(new QVBoxLayout());

	auto edit = new QPlainTextEdit();
	QFont mono = QFontDatabase::systemFont(QFontDatabase::FixedFont);
	edit->setFont(mono);
	layout()->addWidget(edit);

	auto run = new QPushButton("Run");
	connect(run, &QPushButton::pressed, this, [=]() {
		sendText(edit->toPlainText());
	});
	layout()->addWidget(run);
}
