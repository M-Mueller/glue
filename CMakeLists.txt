cmake_minimum_required (VERSION 2.8)
project(glue)

option(BUILD_SAMPLES "Build examples" on)
option(WITH_LIBPNG "Load texture from png files" on)
option(WITH_GLM "Support for glm types (e.g. in GlProgram)" on)
option(WITH_QT "Support for Qt types (e.g. in GlProgram)" on)
option(WITH_EASYLOGGING "Enable logging with easylogging++" on)
option(GL_DEBUG "Enables error checks for all OpenGL calls" on)
option(BUILD_DOCUMENTATION "Generate Doxygen documentation" off)

find_package(PNG)
if(NOT PNG_FOUND)
    set(WITH_LIBPNG off)
endif()

if(WITH_LIBPNG)
    set(GLUE_LIBPNG 1)
    add_definitions(${PNG_DEFINITIONS})
    include_directories(${PNG_INCLUDE_DIRS})
endif()

if(WITH_GLM)
    set(GLUE_GLM 1)
endif()

find_package(Qt5Core)
find_package(Qt5Gui)
if(NOT Qt5Core_FOUND OR NOT Qt5Gui_FOUND)
    set(WITH_QT off)
endif()
if(WITH_QT)
    set(GLUE_QT 1)
endif()

if(WITH_EASYLOGGING)
    set(GLUE_LOGGING 1)
endif()

if(GL_DEBUG)
    set(GLUE_GL_DEBUG 1)
endif()

if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen must be installed to build the documentation.")
    else()
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating Doxygen documentation"
            VERBATIM)
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/glue/GlConfig.h.in include/glue/GlConfig.h)

include_directories(
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

set(SOURCES src/GlBuffer.cpp
        src/GlInternal.cpp
	src/GlProgram.cpp
	src/GlShader.cpp
	src/GlVertexArray.cpp
	src/GlVertexBuffer.cpp
        src/GlIndexBuffer.cpp
        src/GlTexture.cpp
        src/GlTexture1D.cpp
        src/GlTexture2D.cpp
        src/GlTexture3D.cpp
        src/GlFrameBuffer.cpp
        src/GlRenderBuffer.cpp
        src/GlQuery.cpp
	src/glad.c
)

set(HEADERS include/glue/GlBuffer.h
        include/glue/GlInternal.h
        include/glue/GlConfig.h
        include/glue/GlProgram.h
        include/glue/GlShader.h
        include/glue/GlVertexArray.h
        include/glue/GlVertexBuffer.h
        include/glue/GlIndexBuffer.h
        include/glue/GlTexture.h
        include/glue/GlTexture1D.h
        include/glue/GlTexture2D.h
        include/glue/GlTexture3D.h
        include/glue/GlFrameBuffer.h
        include/glue/GlRenderBuffer.h
        include/glue/GlQuery.h
        include/glue/GlUtils.h
)

add_library(glue ${SOURCES} ${HEADERS})
target_link_libraries(glue)

if(WITH_LIBPNG)
    target_link_libraries(glue ${PNG_LIBRARIES})
endif()

if(WITH_QT)
    target_link_libraries(glue Qt5::Core Qt5::Gui)
endif()

if(BUILD_SAMPLES)
    if(WITH_GLM)
        add_subdirectory(samples)
    else()
        message(WARNING "Samples require glm support")
        set(BUILD_SAMPLES off)
    endif()
endif()

install(TARGETS glue ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/glue)
