cmake_minimum_required(VERSION 3.16)

project(DBManagementLab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};C:/Qt/5.15.2/mingw81_64/plugins/sqldrivers")


set(DBManagementLab_SOURCE
    main.cpp
    adddialog.cpp
    connectiondialog.cpp
    mainwindow.cpp
    modifydialog.cpp
    printdialog.cpp
    printgraf.cpp
    qcustomplot.cpp
)


set(DBManagementLab_UI
    adddialog.ui
    connectiondialog.ui
    mainwindow.ui
    modifydialog.ui
    printdialog.ui
    printgraf.ui
)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Sql Widgets PrintSupport AxContainer)

qt5_wrap_ui(UI_HEADERS ${DBManagementLab_UI})

add_compile_options(-w)

add_executable(${PROJECT_NAME} ${DBManagementLab_SOURCE} ${UI_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Sql Qt5::Widgets Qt5::PrintSupport Qt5::AxContainer)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND C:/Qt/5.15.2/mingw81_64/bin/windeployqt.exe -- $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)