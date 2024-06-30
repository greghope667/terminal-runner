#include "console.h"

#include <KPluginFactory>
#include <KParts/ReadOnlyPart>
#include <QStackedLayout>
#include <kde_terminal_interface.h>

#include "main.h"

Console::Console(QWidget* parent)
	: QWidget(parent)
{
	setLayout(new QStackedLayout(this));
	load();
}

Console::~Console()
{
	disconnect(part_, &KParts::ReadOnlyPart::destroyed, this, &Console::load);
}

void Console::load()
{
	static auto* factory = KPluginFactory::loadFactory(QStringLiteral("kf6/parts/konsolepart")).plugin;
	if (!factory)
		fatal(this, "Unable to load konsolepart\n(maybe Konsole not installed?)");

	part_ = factory->create<KParts::ReadOnlyPart>(this);

	if (!part_)
		fatal(this, "Creating konsolepart failed");

	layout()->addWidget(part_->widget());
	connect(part_, &KParts::ReadOnlyPart::destroyed, this, &Console::load);
}

void Console::write(const QString& text)
{
	auto formatted = text.trimmed() + '\n';
	auto term = qobject_cast<TerminalInterface*>(part_);
	term->sendInput(formatted);
}

void Console::interrupt()
{
	write("\003"); // ^C
}

void Console::cwd(const QString& dir)
{
	write("cd " + dir);
}

void Console::clear()
{
	write("clear");
}
