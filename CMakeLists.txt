cmake_minimum_required(VERSION 3.6)
project(1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    data/vars-100-01.cnf
    data/vars-100-02.cnf
    data/vars-100-03.cnf
    data/vars-100-04.cnf
    data/vars-100-05.cnf
    data/vars-100-06.cnf
    data/vars-100-07.cnf
    data/vars-100-08.cnf
    data/vars-100-09.cnf
    data/vars-100-10.cnf
    data/vars-150-01.cnf
    data/vars-150-02.cnf
    data/vars-150-03.cnf
    data/vars-150-04.cnf
    data/vars-150-05.cnf
    data/vars-150-06.cnf
    data/vars-150-07.cnf
    data/vars-150-08.cnf
    data/vars-150-09.cnf
    data/vars-150-10.cnf
    data/vars-200-01.cnf
    data/vars-200-02.cnf
    data/vars-200-03.cnf
    data/vars-200-04.cnf
    data/vars-200-05.cnf
    data/vars-200-06.cnf
    data/vars-200-07.cnf
    data/vars-200-08.cnf
    data/vars-200-09.cnf
    data/vars-200-10.cnf
    data/vars-250-01.cnf
    data/vars-250-02.cnf
    data/vars-250-03.cnf
    data/vars-250-04.cnf
    data/vars-250-05.cnf
    data/vars-250-06.cnf
    data/vars-250-07.cnf
    data/vars-250-08.cnf
    data/vars-250-09.cnf
    data/vars-250-10.cnf
    data/vars-300-01.cnf
    data/vars-300-02.cnf
    data/vars-300-03.cnf
    data/vars-300-04.cnf
    data/vars-300-05.cnf
    data/vars-300-06.cnf
    data/vars-300-07.cnf
    data/vars-300-08.cnf
    data/vars-300-09.cnf
    data/vars-300-10.cnf
    resultats_ok.txt
    resum.txt
    run.sh
    SAT-alumnes.cpp)

add_executable(1 ${SOURCE_FILES})