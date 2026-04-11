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
		include/def/types.hpp
		include/def/version.hpp
		include/def/config.hpp
		include/def/err.hpp
		src/utility/ErrBox.cpp
		include/utility/LocalLogger.hpp
		include/auth/KeyGenerator.hpp
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
		include/utility/StaticKit.hpp
		src/utility/StaticKit.cpp
		
		include/jftp/jftp.hpp
		src/jftp/jftp_holder.cpp
		include/jftp/JftpIO.hpp
		include/jftp/req/JftpRequest.hpp
		include/jftp/rsp/JftpResponse.hpp
		include/jftp/JftpClient.hpp
		include/jftp/JftpServer.hpp
    )
    
    qt_add_executable(FDServerCLI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		src/server/ServerCLI.cpp
    )
    
	qt_add_executable(FDClientCLI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		src/client/ClientCLI.cpp
    )
endif()

include_directories("./include")
target_link_libraries(FileDisc PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)
target_link_libraries(FDServerCLI PRIVATE FileDisc)
target_link_libraries(FDClientCLI PRIVATE FileDisc)





