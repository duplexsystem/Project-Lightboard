#Use Ninja if found
find_program(NINJA_FOUND ninja)
if(NINJA_FOUND)
    SET (CMAKE_GENERATOR Ninja CACHE BOOL "" FORCE)
    message(STATUS "Using Ninja Generator")
endif()

#Use Clang if available
find_program(CLANG_FOUND clang)
if(CLANG_FOUND)
    SET (CMAKE_C_COMPILER "${CLANG_FOUND}" CACHE BOOL "" FORCE)
    message(STATUS "Using Clang C Compiler")
endif()
find_program(CLANGPP_FOUND clang++)
if(CLANGPP_FOUND)
    SET (CMAKE_CXX_COMPILER "${CLANGPP_FOUND}" CACHE BOOL "" FORCE)
    message(STATUS "Using Clang++ C++ Compiler")
endif()
