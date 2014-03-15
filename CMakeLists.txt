cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Depends on Qt.
set(Target_Name QtCoreUtilities)
set(CAP_Target_Name QT_CORE_UTILITIES)
message(<${Target_Name}>)

## vedgTools/CMakeModules path boilerplate.
include(vedgTools/CMakeLicense OPTIONAL RESULT_VARIABLE CMakeModulesWasIncluded)
if(CMakeModulesWasIncluded STREQUAL NOTFOUND)
    set(CMAKE_MODULE_PATH
            "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
    message("Including CMakeModules.")
    include(vedgTools/CMakeLicense)
endif()

# NOTE: QtCore is the only module, used by this library.
include(vedgTools/LibraryQtStart)

include(vedgTools/LibraryWithQtInit)


include(vedgTools/LibraryFindQt)
libraryFindQt(Qt5Core . QTCORE)


set(Sources_Path src)

include_directories(
    ${${Target_Name}_PublicHeaders_Path}
    ${${Target_Name}_PublicHeaders_Path}/${Target_Name}
)

set(Sources
    ${Sources_Path}/Error.cpp ${Sources_Path}/String.cpp
)


include(vedgTools/LibraryAddTarget)

include(vedgTools/LinkQt)
linkQt(${Target_Name} Core . ${QT_QTCORE_LIBRARY})


set_target_properties(${Target_Name} PROPERTIES
                        PUBLIC_HEADER "Error.hpp;String.hpp")

message(</${Target_Name}>)
