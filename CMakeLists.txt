cmake_minimum_required(VERSION 3.0)
project(grafo_lista_de_adjacencias CXX)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage") #codecov
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.travis/cmake) # modulo para codecov
find_package(GTest REQUIRED)

set(HEADERS
        src/grafo_lista_adj/grafolistaadjexercicio.h
        )

set(SOURCES
        src/grafo_lista_adj/grafolistaadjexercicio.cpp
        )

set(TESTS
        tests/grafoListaAdj.test.h
        tests/testMenorCaminho.test.h
        )
        

enable_testing()
include(CodeCoverage)

add_executable(grafo_lista_de_adjacencias src/main.cpp ${HEADERS} ${SOURCES} )

add_executable(runUnitTests src/main.test.cpp ${HEADERS} ${SOURCES} ${TESTS} )

target_link_libraries(runUnitTests GTest::GTest GTest::Main)

setup_target_for_coverage(coverage  runUnitTests  coverage)
