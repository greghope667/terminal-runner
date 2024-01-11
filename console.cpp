#include "console.h"

#include <KPluginFactory>
#include <KParts/ReadOnlyPart>
#include <QLayout>
#include <kde_terminal_interface.h>

#include "main.h"

Console::Console(QWidget* parent)
	: QWidget(parent)
{
	setLayout(new QVBoxLayout(this));
	closed();
}

Console::~Console()
{
	disconnect(part_, &KParts::ReadOnlyPart::destroyed, this, &Console::closed);
}

void Console::closed()
{
	part_ = nullptr;
	load();
}

void Console::load()
{
	if (part_) return;

	static auto* factory = KPluginFactory::loadFactory(QStringLiteral("konsolepart")).plugin;
	if (!factory)
		fatal(this, "Unable to load konsolepart\n(maybe Konsole not installed?)");

	part_ = factory->create<KParts::ReadOnlyPart>(this);

	if (!part_)
		fatal(this, "Creating konsolepart failed");

	layout()->addWidget(part_->widget());
	connect(part_, &KParts::ReadOnlyPart::destroyed, this, &Console::closed);
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
