string(TOLOWER ${PROJECT_NAME} ExecutableName)

file(GLOB_RECURSE "${ExecutableName}_SOURCES" RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
list(REMOVE_ITEM ${ExecutableName}_SOURCES pch.h)

if(NOT WIN32)
	list(FILTER ${ExecutableName}_SOURCES EXCLUDE REGEX "_windows.(cpp|h)")
elseif(NOT UNIX)
	list(FILTER ${ExecutableName}_SOURCES EXCLUDE REGEX "_unix.(cpp|h)")
endif()

message(STATUS "${ExecutableName}_SOURCES: ${${ExecutableName}_SOURCES}")

add_executable(${ExecutableName} WIN32 ${${ExecutableName}_SOURCES})
target_include_directories(${ExecutableName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${ExecutableName}
	glad
	fmt::fmt-header-only)

target_compile_definitions(${ExecutableName} PRIVATE DEBUG=$<IF:$<CONFIG:Debug>,1,0>)

if(supportsIPO)
	set_target_properties(${ExecutableName} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

target_precompile_headers(${ExecutableName} PRIVATE pch.h)

if(WIN32)
	target_compile_definitions(${ExecutableName} PRIVATE PLATFORM_WINDOWS)
	target_link_libraries(${ExecutableName} winmm.lib Opengl32.lib)
elseif(UNIX)
	target_compile_definitions(${ExecutableName} PRIVATE PLATFORM_UNIX)
	find_package(TBB REQUIRED)
	target_link_libraries(${ExecutableName} TBB::tbb)
endif()

if(MSVC)
	target_compile_options(${ExecutableName} PRIVATE
		"$<$<COMPILE_LANGUAGE:CXX>:/Wall;/MP;/Oi;/GL;$<$<CONFIG:RELEASE>:/Ot;/GR->>")

	# Disable exceptions: https://cmake.org/pipermail/cmake/2010-December/041641.html
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc ")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()

	if(CMAKE_CXX_FLAGS MATCHES "/EHsc$")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()

	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ExecutableName})
elseif (CMAKE_CXX_COMPILER_ID MATCHES "(Clang|GNU)")
	target_compile_options(${ExecutableName} PRIVATE
	"$<$<COMPILE_LANGUAGE:CXX>:-Wall;-Wextra;-Wpedantic;-Wconversion;-fno-rtti;$<$<CONFIG:RELEASE>:-O3;-ffast-math>>")
endif()