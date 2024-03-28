cmake_minimum_required(VERSION 3.15)

project(SNL VERSION 1.0)

add_executable(snl
    main.cpp
    services/services.cpp
    models/models.cpp
)

target_include_directories(snl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} services models)