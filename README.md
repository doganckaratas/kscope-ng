# kscope-ng
Qt based IDE/Editor inspired from KDE KScope, entirely written from scratch 

## Compilation
    $ qmake
    $ make

## Roadmap

- Implement Event.cpp, Action.cpp, View.cpp
- Actually, Events.cpp must be abstract and inherited by EditorEvents.cpp and WindowEvents.cpp
- Also Action.cpp must be same as Events classes
- View.cpp needs to be setup all UI elements, in another thread.
- Add Dynamic Line Numbering
- Add Custom highlighters
- Run QScintilla component and its' instances in another thread
- ~Add Find&Replace~
- ~Add CScope wrapper~
- Refactor marked methods
- Delete View XML and implement them with C++ (same with #4)
- Fix Windows release
- We need a cool and sleek icon :o
