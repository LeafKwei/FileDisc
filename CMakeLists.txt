cmake_minimum_required(VERSION 3.16)

project(FileDisc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
	
		
		
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FileDisc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		src/jstp/JstpServer.cpp
		src/jstp/JstpClient.cpp
		include/jstp/JstpServer.hpp
		include/jstp/JstpClient.hpp
		include/def/types.hpp
		include/def/version.hpp
		include/def/config.hpp
		include/def/err.hpp
		src/client/test_jstpclient.cpp
		include/jstp/RequestHook.hpp
		include/jstp/JstpPayload.hpp
		include/server/server_holder.hpp
		src/server/server_holder.cpp
		src/utility/ErrBox.cpp
		src/client/test_jstpserver.cpp
		include/utility/LocalLogger.hpp
		include/auth/KeyGenerator.hpp
		include/jstp/jstp.hpp
		src/jstp/JstpPayload.cpp
		include/jstp/jobs/JstpJob.hpp
		src/jstp/jobs/JstpJob.cpp
		include/utility/Defer.hpp
		include/thread/Job.hpp 
		include/thread/JobQueue.hpp 
		include/thread/ManagerInf.hpp 
		include/thread/ThreadManager.hpp 
		include/thread/ThreadRunner.hpp
		src/thread/JobQueue.cpp 
		src/thread/ManagerInf.cpp 
		src/thread/ThreadManager.cpp 
		src/thread/ThreadRunner.cpp
		include/thread/RunnerInf.hpp
		src/utility/Defer.cpp
		
		src/thread/Job.cpp
		include/thread/jobs/CntledJob.hpp
		src/thread/jobs/CntledJob.cpp
		src/thread/RunnerInf.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FileDisc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FileDisc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FileDisc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories("./include")
target_link_libraries(FileDisc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FileDisc)
endif()
set_target_properties(FileDisc PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS FileDisc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FileDisc)
endif()




