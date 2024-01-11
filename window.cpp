#include "window.h"

#include "console.h"
#include "editor.h"

#include <QDockWidget>
#include <QToolBar>

MainWindow::MainWindow()
	: QMainWindow()
	, console_(new Console(this))
{
	auto toolbar = new QToolBar();
	toolbar->addAction("New Command", this, &MainWindow::addEditor);
	toolbar->addAction("Interrupt", console_, &Console::interrupt);
	addToolBar(toolbar);
	setCentralWidget(console_);
}

void MainWindow::addEditor()
{
	auto dock = new QDockWidget(">_");
	auto editor = new Editor();
	dock->setWidget(editor);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	connect(editor, &Editor::sendText, console_, &Console::write);
}
