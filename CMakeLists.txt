﻿cmake_minimum_required(VERSION 3.16)

project(WHLdi_01 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#test
#test
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(WHLdi_01
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        File/filecommanddialog.h File/filecommanddialog.cpp
        Camera/camerasettingdialog.h Camera/camerasettingdialog.cpp
        Common/messageboxdlg.h Common/messageboxdlg.cpp
        Common/frmmessagebox.h Common/frmmessagebox.cpp
        res.qrc
        Motion/motionparadialog.h Motion/motionparadialog.cpp
        Motion/motioninfodialog.h Motion/motioninfodialog.cpp
        Motion/motionconnecdialog.h Motion/motionconnecdialog.cpp
        Motion/axissettingtab.h Motion/axissettingtab.cpp
        Motion/runinsettingtab.h Motion/runinsettingtab.cpp
        Motion/comboboxmotiondelegate.h Motion/comboboxmotiondelegate.cpp
        Motion/inpudialogmotiondelegate.h Motion/inpudialogmotiondelegate.cpp
        Motion/iomapinputdialog.h Motion/iomapinputdialog.cpp
        Motion/inputdigitaldelegate.h Motion/inputdigitaldelegate.cpp
        Motion/basicsparameter.h Motion/basicsparameter.cpp
        Motion/motionEnum.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET WHLdi_01 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(WHLdi_01 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(WHLdi_01
            ${PROJECT_SOURCES}
        )
    endif()
endif()


###### 相对路径
set(LeiSai_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdPart/LeiSai/leisai_lib/include")
set(LeiSai_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdPart/LeiSai/leisai_lib/LTSMC.lib")
target_include_directories( WHLdi_01 PRIVATE ${LeiSai_INCLUDE_DIR})
target_link_libraries(WHLdi_01 PRIVATE ${LeiSai_LIBRARY})

###### 绝对路径
# include_directories("D:/WHLdi_01/ThirdPart/LeiSai/leisai_lib/include")
# target_link_libraries(WHLdi_01 PRIVATE D:/WHLdi_01/ThirdPart/LeiSai/leisai_lib/LTSMC.lib)


target_include_directories(WHLdi_01 PRIVATE
    ${CMAKE_SOURCE_DIR}/File
    ${CMAKE_SOURCE_DIR}/Camera
    ${CMAKE_SOURCE_DIR}/Motion
    ${CMAKE_SOURCE_DIR}/Common

)
target_link_libraries(WHLdi_01 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WHLdi_01)
endif()
set_target_properties(WHLdi_01 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS WHLdi_01
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WHLdi_01)
endif()
