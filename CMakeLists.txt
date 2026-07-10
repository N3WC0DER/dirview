cmake_minimum_required(VERSION 3.16)
project(dirview LANGUAGES CXX)

# 1. Enable automatic compilation of Meta-Objects, UI files, and Resources
set(CMAKE_AUTOMOC ON)   # Handles Q_OBJECT macros
set(CMAKE_AUTOUIC ON)   # Processes .ui files
set(CMAKE_AUTORCC ON)   # Processes .qrc files
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Ensures MOC files are discoverable

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Locate the Qt5 packages
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# 3. Define source files
set(PROJECT_SOURCES
    main.cpp
)

# 4. Create the executable binary
add_executable(dirview ${PROJECT_SOURCES})

# 5. Link Qt5 dependencies to your binary
target_link_libraries(dirview PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
