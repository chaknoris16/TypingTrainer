cmake_minimum_required(VERSION 3.21)

project(TypingTrainer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(BUILD_TEST_LIBRARY ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resultwindow.cpp
    resultwindow.h
    resultwindow.ui
    resurce.qrc
    startwindow.cpp
    startwindow.h
    startwindow.ui
    typingtestingpage.h typingtestingpage.cpp
    vector_of_exercises.h  vector_of_exercises.cpp
    virtual_keyboard.h virtual_keyboard.cpp
    jsonconfigparser.h jsonconfigparser.cpp
    tableoutput.h tableoutput.cpp
    keyboardlayoutlanguagecontroller.h keyboardlayoutlanguagecontroller.cpp
    incorrectkeyboardlayout.h incorrectkeyboardlayout.cpp incorrectkeyboardlayout.ui
    IDBManager.h
    DBTreningQuery.h
    DBTestingQuery.h
    IJsonTextParser.h
    RandomElementPicker.h
    IRandomTextProvider.h
    IColorizeCharacter.h
    CharacterColorist.h
    ITypingSpeedCalculator.h
    TypingSpeedCalculator.h
    CostomComboBox.h
    ComboBoxManager.h
    ResourceCopier.h
)

if(BUILD_TESTS)
    add_library(TypingTrainer_lib ${PROJECT_SOURCES}
        )
    target_link_libraries(TypingTrainer_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
    enable_testing()
endif()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

qt_add_executable(TypingTrainer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


)
endif()

target_link_libraries(TypingTrainer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TypingTrainer)
endif()
set_target_properties(TypingTrainer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#add_compile_definitions(BUILD_TESTS)

include(GNUInstallDirs)
install(TARGETS TypingTrainer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TypingTrainer)
endif()
