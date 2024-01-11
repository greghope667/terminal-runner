add_requires("cmake::KF5Parts", {system = true, configs = {link_libraries="KF5::Parts"}})

set_languages("c++17")
add_cxflags("-O")

target("terminal-runner")
	add_rules("qt.widgetapp")
	add_files("*.h") -- for qt moc
	add_files("*.cpp")
	add_frameworks("QtGui")
	add_packages("cmake::KF5Parts")

	-- Output compile commands
	after_build(function (target)
		import("core.project.task")
		task.run("project", {kind = "compile_commands", outputdir="."})
	end)

