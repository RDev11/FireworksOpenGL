#cmake -DCMAKE_GENERATOR_PLATFORM=x64 . 

cmake_minimum_required(VERSION 3.6)
IF(NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE) 
ENDIF()
set (project "GlFireworks" ) #LANGUAGES C CXX
project (${project})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${project})
#set (gRPC_INSTALL_LIBDIR "lib" CACHE STRING "Installation directory for libraries")
#option(gRPC_BUILD_CODEGEN "Build codegen" ON)
#file (GLOB FOO "src/*.cpp")
#set (DIR_INCLUDE ${DIR_INCLUDE} "include")

#${CMAKE_CURRENT_BINARY_DIR}


#FIND_PACKAGE(OpenGL REQUIRED)
#LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
#INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

IF(WIN32)
    # hide insecure CRT warnings, common practice
    #ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    #IF(MSVC)
    #    SET( CMAKE_DEBUG_POSTFIX "d" )
    #ENDIF(MSVC)
ENDIF()

set(srcList 
	"src/main.cpp"
	"src/App.h"
	"src/App.cpp"
	"src/GameObject.h"
	"src/Particle.h"
	"src/Particle.cpp"
	"src/utls.h"
	)



add_executable(${project} ${srcList})
target_include_directories (${project} 
	PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/include
	${CMAKE_CURRENT_SOURCE_DIR}/include
	)
#message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/include)
set_target_properties(
	${project} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUEIRED ON)

#${OPENGL_glu_LIBRARY} glu32
#opengl32
#target_link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/lib/$(Configuration)/ )

find_library(LIB_freeglut freeglut PATH thirdparty/freeglut/lib/Release)
find_library(LIB_freeglutD freeglutd PATH thirdparty/freeglut/lib/Debug)

target_link_libraries(${project} 
	optimized ${LIB_freeglut} 
	debug  ${LIB_freeglutD})


configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/bin/Release/freeglut.dll
			   	${CMAKE_CURRENT_BINARY_DIR}/Release/freeglut.dll
			   	COPYONLY)

configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/bin/Debug/freeglutd.dll
			   	${CMAKE_CURRENT_BINARY_DIR}/Debug/freeglutd.dll
			   	COPYONLY)

configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/bin/Debug/freeglutd.ilk
			   	${CMAKE_CURRENT_BINARY_DIR}/Debug/freeglutd.ilk
			   	COPYONLY)

configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/bin/Debug/freeglutd.pdb
			   	${CMAKE_CURRENT_BINARY_DIR}/Debug/freeglutd.pdb
			   	COPYONLY)




target_include_directories (${project} 
	PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/soil/include
	)
find_library(LIB_soil soil PATH thirdparty/soil/Release)
find_library(LIB_soilD soil PATH thirdparty/soil/Debug)

target_link_libraries(${project} 
	optimized ${LIB_soil} 
	debug  ${LIB_soilD})

#ResIL 
#target_include_directories (${project} 
#	PRIVATE 
#	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ResIL/include
#	)
#find_library(LIB_ILU ILU PATH thirdparty/ResIL)
#target_link_libraries(${project} ${LIB_ILU}) 
#find_library(LIB_ILUT ILUT PATH thirdparty/ResIL)
#target_link_libraries(${project} ${LIB_ILUT}) 
#find_library(LIB_ResIL ResIL PATH thirdparty/ResIL)
#target_link_libraries(${project} ${LIB_ResIL}) 

#add_custom_command(
#        TARGET ${project} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/LUL/
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/freeglut/bin/$(Configuration)/freeglut.dll
#               ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)/freeglut.dll)


#


###
# Копипастим папку Media в папку, где будет exe'шник: Release & Debug
file(GLOB mediaFiles
    "media/*"
    "media/*/*"
    "media/*/*/*"
    "media/*/*/*/*"
)
foreach(mfile ${mediaFiles})
	 
	#get_filename_component(mfile_name ${mfile} NAME)

	#message(STATUS ${mfile} " =>  " ${mfile_out})
	if(IS_DIRECTORY ${mfile})
		#message(${mfile}" =>  "${CMAKE_CURRENT_BINARY_DIR}/Debug/media/${mfile_name})
	else()
		string(REPLACE 
				${CMAKE_CURRENT_SOURCE_DIR}#<match-string> 
				${CMAKE_CURRENT_BINARY_DIR}/Debug #<replace-string> 
				mfile_out #<out-var> 
				${mfile}
				)

		configure_file(	${mfile}
			   			${mfile_out}
			   			COPYONLY)
	    ###########
		string(REPLACE 
				${CMAKE_CURRENT_SOURCE_DIR}#<match-string> 
				${CMAKE_CURRENT_BINARY_DIR}/Release #<replace-string> 
				mfile_out #<out-var> 
				${mfile}
				)

		configure_file(	${mfile}
			   			${mfile_out}
			   			COPYONLY)
	endif()
endforeach()