cmake_minimum_required(VERSION 3.14)

project(Thermonator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Bluetooth LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Bluetooth LinguistTools REQUIRED)

set(TS_FILES Thermonator_de_DE.ts)

set(PROJECT_SOURCES
        main.cpp      
        backend/eq3Thermostat/command/ConfigureComfortAndEcoTemperatureCommand.hpp
        backend/eq3Thermostat/command/ConfigureComfortAndEcoTemperatureCommand.cpp
        backend/eq3Thermostat/command/ConfigureOpenWindowModeCommand.hpp
        backend/eq3Thermostat/command/ConfigureOpenWindowModeCommand.cpp
        backend/eq3Thermostat/command/GetDayTimerCommand.hpp
        backend/eq3Thermostat/command/GetDayTimerCommand.cpp
        backend/eq3Thermostat/command/GetSerialNumberCommand.hpp
        backend/eq3Thermostat/command/GetSerialNumberCommand.cpp
        backend/eq3Thermostat/command/SetBoostOffCommand.hpp
        backend/eq3Thermostat/command/SetBoostOffCommand.cpp
        backend/eq3Thermostat/command/SetBoostOnCommand.hpp
        backend/eq3Thermostat/command/SetBoostOnCommand.cpp
        backend/eq3Thermostat/command/SetComfortTemperatureCommand.hpp
        backend/eq3Thermostat/command/SetComfortTemperatureCommand.cpp
        backend/eq3Thermostat/command/SetCurrentDateTimeCommand.hpp
        backend/eq3Thermostat/command/SetCurrentDateTimeCommand.cpp    
        backend/eq3Thermostat/command/SetDayTimerCommand.hpp
        backend/eq3Thermostat/command/SetDayTimerCommand.cpp
        backend/eq3Thermostat/command/SetEcoTemperatureCommand.hpp
        backend/eq3Thermostat/command/SetEcoTemperatureCommand.cpp
        backend/eq3Thermostat/command/SetHardwareButtonsLockCommand.hpp
        backend/eq3Thermostat/command/SetHardwareButtonsLockCommand.cpp
        backend/eq3Thermostat/command/SetHardwareButtonsUnlockCommand.hpp
        backend/eq3Thermostat/command/SetHardwareButtonsUnlockCommand.cpp
        backend/eq3Thermostat/command/SetTemperatureCommand.hpp
        backend/eq3Thermostat/command/SetTemperatureCommand.cpp
        backend/eq3Thermostat/command/SetTemperatureOffsetCommand.hpp
        backend/eq3Thermostat/command/SetTemperatureOffsetCommand.cpp
        backend/eq3Thermostat/command/SetThermostatOffCommand.hpp
        backend/eq3Thermostat/command/SetThermostatOffCommand.cpp
        backend/eq3Thermostat/command/SetThermostatOnCommand.hpp
        backend/eq3Thermostat/command/SetThermostatOnCommand.cpp
        backend/eq3Thermostat/notification/GetDayTimerNotification.hpp
        backend/eq3Thermostat/notification/GetDayTimerNotification.cpp
        backend/eq3Thermostat/notification/SerialNumberNotification.hpp
        backend/eq3Thermostat/notification/SerialNumberNotification.cpp
        backend/eq3Thermostat/notification/SetDayTimerNotification.hpp
        backend/eq3Thermostat/notification/SetDayTimerNotification.cpp
        backend/eq3Thermostat/notification/StatusNotification.hpp
        backend/eq3Thermostat/notification/StatusNotification.cpp
        backend/eq3Thermostat/types/AsciiSign.hpp
        backend/eq3Thermostat/types/AsciiSign.cpp
        backend/eq3Thermostat/types/Date.hpp
        backend/eq3Thermostat/types/Date.cpp
        backend/eq3Thermostat/types/DateTime.hpp
        backend/eq3Thermostat/types/DateTime.cpp
        backend/eq3Thermostat/types/DayOfWeek.hpp
        backend/eq3Thermostat/types/DayOfWeek.cpp  
        backend/eq3Thermostat/types/DayTimer.hpp
        backend/eq3Thermostat/types/DayTimer.cpp
        backend/eq3Thermostat/types/DayTimerEntries.hpp
        backend/eq3Thermostat/types/DayTimerEntries.cpp
        backend/eq3Thermostat/types/DayTimerEntry.hpp
        backend/eq3Thermostat/types/DayTimerEntry.cpp     
        backend/eq3Thermostat/types/OpenWindowInterval.hpp
        backend/eq3Thermostat/types/OpenWindowInterval.cpp
        backend/eq3Thermostat/types/SerialNumber.hpp
        backend/eq3Thermostat/types/SerialNumber.cpp    
        backend/eq3Thermostat/types/Status.hpp
        backend/eq3Thermostat/types/Status.cpp
        backend/eq3Thermostat/types/StatusFlags.hpp
        backend/eq3Thermostat/types/StatusFlags.cpp      
        backend/eq3Thermostat/types/Temperature.hpp
        backend/eq3Thermostat/types/Temperature.cpp
        backend/eq3Thermostat/types/TemperatureOffset.hpp
        backend/eq3Thermostat/types/TemperatureOffset.cpp
        backend/eq3Thermostat/types/Time.hpp
        backend/eq3Thermostat/types/Time.cpp
        backend/eq3Thermostat/types/UnknownStatusByte.hpp
        backend/eq3Thermostat/types/UnknownStatusByte.cpp
        backend/eq3Thermostat/types/ValvePosition.hpp
        backend/eq3Thermostat/types/ValvePosition.cpp
        backend/eq3Thermostat/types/WeekTimer.hpp
        backend/eq3Thermostat/types/WeekTimer.cpp
        backend/eq3Thermostat/Controller.hpp
        backend/eq3Thermostat/Controller.cpp
        backend/eq3Thermostat/Eq3Thermostat.hpp
        backend/eq3Thermostat/Eq3Thermostat.cpp
        backend/eq3Thermostat/IOService.hpp
        backend/eq3Thermostat/IOService.cpp
        backend/gui/WindowManager.hpp
        backend/gui/WindowManager.cpp
        backend/gui/pages/scanConnectPage/ScanConnectPageController.hpp
        backend/gui/pages/scanConnectPage/ScanConnectPageController.cpp
        backend/gui/pages/scanConnectPage/ScannedDevice.hpp
        backend/gui/pages/scanConnectPage/ScannedDevice.cpp
        backend/gui/pages/scanConnectPage/ScannedDevicesModel.hpp
        backend/gui/pages/scanConnectPage/ScannedDevicesModel.cpp
        backend/utility/EnumToString.hpp
        backend/utility/Utility.hpp
        backend/utility/Utility.cpp     
        backend/ConnectionHandler.hpp
        backend/ConnectionHandler.cpp
        backend/DeviceManager.hpp
        backend/DeviceManager.cpp
        backend/DeviceScanner.hpp
        backend/DeviceScanner.cpp
        backend/ServiceScanner.hpp
        backend/ServiceScanner.cpp
        qml/qml.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Thermonator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Thermonator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Thermonator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Thermonator
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(Thermonator
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Thermonator
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Bluetooth)

set_target_properties(Thermonator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Thermonator)
    qt_finalize_executable(Thermonator)
endif()
