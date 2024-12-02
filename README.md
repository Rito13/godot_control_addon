# This is Control++ godot plugin.

## ---- Description ----

This plugin adds control classes usefull for creating animated bars and tabs.
Firstly [RevisedButton](markdown_doc/RevisedButton.md) is a class similar to godot Button but uses RichTextLable to show contained text and automatically scrols it when it exceeds bounds using [AutoScroll](markdown_doc/AutoScroll.md) class.
[ExpandableButton](markdown_doc/ExpandableButton.md) inherits from [RevisedButton](markdown_doc/RevisedButton.md) but normally displays only text or image and both when hovered by mouse.
[AnimatedBar](markdown_doc/AnimatedBar.md) can be used for example to create ToolBar. It automaticaly resizes and rearranges its children and implements navigation mechanism if there are too many of them. It comes in two versions [vertical](markdown_doc/VAnimatedBar.md) and [horizontal](markdown_doc/HAnimatedBar.md).
[AnimatedTabContainer](markdown_doc/AnimatedTabContainer.md) uses [AnimatedBar](markdown_doc/AnimatedBar.md) to determine which child needs to be displayed similarly to godot TabContainer but does this with simple animation. It can support multiple [AnimatedBar](markdown_doc/AnimatedBar.md) children at the same time.
[IrregularGridContainer](markdown_doc/IrregularGridContainer.md) is very usefull for arranging [ExpandableButton](markdown_doc/ExpandableButton.md) in rows and columns because it preserves additional space for them to expand in. Apart from that it rearranges its children in rows using theirs strech ratio property.

Here is a link to [Source Code](https://github.com/Rito13/godot_control_addon).

## ---- Instalation ----

Download latest release from [GitHub](https://github.com/Rito13/godot_control_addon/releases) or install using [Godot Asset Library](https://godotengine.org/asset-library/asset/{This_addon_ID}).

## ---- TODO ----
 - Allow [AnimatedTabContainer](markdown_doc/AnimatedTabContainer.md) to have bars on left and upper side.
 - Fix [ExpandableButton](markdown_doc/ExpandableButton.md) draw two images.
 - Fix [ExpandableButton](markdown_doc/ExpandableButton.md) not overwriting [RevisedButton](markdown_doc/RevisedButton.md) behavior of positioning text.
 - Allow [ExpandableButton](markdown_doc/ExpandableButton.md) to expand left (and maybe up and/or down).
 - Allow [ExpandableButton](markdown_doc/ExpandableButton.md) to have normal and additional text in the same time.
 - Allow [ExpandableButton](markdown_doc/ExpandableButton.md) to have normal and additional image in the same time.
 - Expose API for creating [AnimatedBar](markdown_doc/AnimatedBar.md)s.
 - Create/Expose additional functions of [AnimatedBar](markdown_doc/AnimatedBar.md) and [AnimatedTabContainer](markdown_doc/AnimatedTabContainer.md) classes.
 - Rename or delete [GDExample](markdown_doc/GDExample.md) class.
 - Make [IrregularGridContainer](markdown_doc/IrregularGridContainer.md) more usefull, maybe like this [SpanningTableContainer](https://github.com/Magodra/SpanningTableContainer) addon.
 - Think about circles and triangles.
 - Decreas CPU consumption of some classes (eg. [RevisedButton](markdown_doc/RevisedButton.md)).
 - Make better use of Godot theme API.
 - Connect/Automate version number actualisations to commiting and releasing.
 - Beautify source code.
 - Make so markdown documentation is generated more beautiful.
 - Use `import module_name;` syntax in c++ sources files.
 - Beautify Logo (e.g. bend vertical axis of pluses).
