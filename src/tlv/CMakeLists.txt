cmake_minimum_required (VERSION 3.0)

project (lydia_tlv C)

INCLUDE_DIRECTORIES(../)
INCLUDE_DIRECTORIES(../common)

SET(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/tlv.c
    ${CMAKE_CURRENT_LIST_DIR}/test_tlv.c
    )

add_executable(${PROJECT_NAME} ${SOURCES})