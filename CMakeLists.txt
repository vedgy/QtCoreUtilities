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


# If you want to override default bool strings ("0" and "1") that are used in
# String conversions, set properties QtUtilities_False_String and
# QtUtilities_True_String BEFORE including (adding subdirectory)
# QtCoreUtilities. For example:
# * in library that uses QtCoreUtilities:
# set_property(GLOBAL PROPERTY QtUtilities_False_String "false")
# set_property(GLOBAL PROPERTY QtUtilities_True_String "true")
# set(PATH_TO_QT_CORE_UTILITIES modules/vedgTools/QtCoreUtilities)
# include(vedgTools/LibraryGetQtCoreUtilitiesPublicHeaders)
# * in executable that uses QtCoreUtilities:
# set_property(GLOBAL PROPERTY QtUtilities_False_String "F")
# set_property(GLOBAL PROPERTY QtUtilities_True_String "T")
# add_subdirectory(modules/vedgTools/QtCoreUtilities)
# executableGetPublicHeadersProperty(QtCoreUtilities)
include(vedgTools/GetGlobalProperty)
getGlobalProperty(QtUtilities_False_String "0")
getGlobalProperty(QtUtilities_True_String "1")
add_definitions(
    -DQT_UTILITIES_FALSE_STRING=\"${QtUtilities_False_String}\"
    -DQT_UTILITIES_TRUE_STRING=\"${QtUtilities_True_String}\"
)
message("QtUtilities_False_String = \"${QtUtilities_False_String}\"")
message("QtUtilities_True_String = \"${QtUtilities_True_String}\"")
if(QtUtilities_False_String STREQUAL QtUtilities_True_String)
    message(FATAL_ERROR "False_String must not be equal to True_String!")
endif()


set(Sources_Path src)

include_directories(
    ${${Target_Name}_PublicHeaders_Path}
    ${${Target_Name}_PublicHeaders_Path}/${Target_Name}
)

set(Sources
    ${Sources_Path}/String.cpp
)


include(vedgTools/LibraryAddTarget)

include(vedgTools/LinkQt)
linkQt(${Target_Name} Core . ${QT_QTCORE_LIBRARY})


set_target_properties(${Target_Name} PROPERTIES
                        PUBLIC_HEADER "Error.hpp;String.hpp;Validation.hpp")

message(</${Target_Name}>)
