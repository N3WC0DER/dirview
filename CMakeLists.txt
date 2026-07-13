cmake_minimum_required(VERSION 3.16)
project(dirview LANGUAGES CXX)

# 1. Enable automatic compilation of Meta-Objects, UI files, and Resources
set(CMAKE_AUTOMOC ON)   # Handles Q_OBJECT macros
set(CMAKE_AUTOUIC OFF)   # Processes .ui files
set(CMAKE_AUTORCC OFF)   # Processes .qrc files
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Ensures MOC files are discoverable

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Locate the Qt5 packages
find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)

# 3. Define source files
set(PROJECT_SOURCES
    src/main.cpp
    src/ui/DirectoryViewerWidget.cpp
    src/ui/DirectoryViewerWidget.h
    src/fs/FilterProxyModel.h
    src/fs/FilterProxyModel.cpp
    src/fs/FolderSizeProxyModel.h
    src/fs/FolderSizeProxyModel.cpp
    src/fs/ModelFactory.h
    src/fs/ModelFactory.cpp
    src/fs/FilterController.h
    src/fs/FilterController.cpp
    src/utils/Options.hpp
    src/utils/CalculateSize.hpp
)

# 3.1 Formatting
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_CXX_FILES}
        COMMENT "Formatting code with clang-format..."
    )
endif()

# 3.2 Tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Требуется для работы линтеров

find_program(CLANG_TIDY_EXE clang-tidy)
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=-*,bugprone-*,modernize-*,performance-*,readability-*")
endif()

find_program(CLAZY_EXE clazy)
if(CLAZY_EXE)
    set(CMAKE_CXX_COMPILER_LAUNCHER clazy)
endif()

# 4. Create the executable binary
add_executable(dirview ${PROJECT_SOURCES})

# 5. Link Qt5 dependencies to your binary
target_link_libraries(dirview PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

include(GNUInstallDirs)

install(TARGETS dirview
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
