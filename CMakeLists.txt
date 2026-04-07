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
	qt_add_library(FileDisc STATIC
        ${PROJECT_SOURCES}
		src/jstp/JstpServer.cpp
		src/jstp/JstpClient.cpp
		include/jstp/JstpServer.hpp
		include/jstp/JstpClient.hpp
		include/def/types.hpp
		include/def/version.hpp
		include/def/config.hpp
		include/def/err.hpp
		include/jstp/RequestHook.hpp
		include/jstp/JstpPayload.hpp
		include/server/server_holder.hpp
		src/server/server_holder.cpp
		src/utility/ErrBox.cpp
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
		include/jstp/JstpEmiter.hpp
		include/jstp/jobs/ReqHostJob.hpp
		src/jstp/jobs/ReqHostJob.cpp
		include/utility/StaticKit.hpp
		src/utility/StaticKit.cpp
    )
    
    qt_add_executable(FileDiscClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		src/client/test_jstpclient.cpp
    )
    
	qt_add_executable(FileDiscServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		src/client/test_jstpserver.cpp
    )
endif()

include_directories("./include")
target_link_libraries(FileDisc PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)
target_link_libraries(FileDiscClient PRIVATE libfidi)
target_link_libraries(FileDiscServer PRIVATE libfidi)





