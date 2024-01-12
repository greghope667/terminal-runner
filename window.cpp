#include "window.h"

#include "console.h"
#include "editor.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QToolBar>
#include <QGuiApplication>

MainWindow::MainWindow()
	: QMainWindow()
	, console_(new Console(this))
{
	auto toolbar = new QToolBar();
	toolbar->addAction("New Command", this, &MainWindow::addEditor);
	toolbar->addAction("Choose Dir", [=]() {
		auto dir = QFileDialog::getExistingDirectory(this, "Choose Dir");
		console_->cwd(dir);
	});
	toolbar->addAction("Interrupt", console_, &Console::interrupt);
	toolbar->addAction("Clear", console_, &Console::clear);

	addToolBar(toolbar);
	setCentralWidget(console_);
}

static void setFeatures(QDockWidget* dock)
{
	/* Floating dock windows isn't supported on Wayland.
	 * Hopefully this gets fixed in a future Qt release
	 */
	static bool noFloat = []{
		return QGuiApplication::platformName() == "wayland";
	}();

	if (noFloat) {
		dock->setFeatures(dock->features() & ~QDockWidget::DockWidgetFloatable);
	}
}

void MainWindow::addEditor()
{
	auto dock = new QDockWidget(">_");
	auto editor = new Editor();
	dock->setWidget(editor);
	setFeatures(dock);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	connect(editor, &Editor::sendText, console_, &Console::write);
}
