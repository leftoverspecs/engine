function(target_assets TARGET)
    cmake_parse_arguments(PARSE_ARGV 1 "ta" "" "" "PRIVATE;PUBLIC;INTERFACE")
    foreach(ACCESS PRIVATE PUBLIC INTERFACE)
        foreach(ASSET ${ta_${ACCESS}})
            get_filename_component(NAME ${ASSET} NAME)
            string(REPLACE "-" "_" NAME ${NAME})
            string(REPLACE "." "_" NAME ${NAME})
            set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${ASSET}.h")
            add_custom_command(OUTPUT ${OUTPUT}
                COMMAND
                    ${Python3_EXECUTABLE}
                    "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/hex_converter.py"
                    "${ASSET}"
                    "${NAME}"
                    "${OUTPUT}"
                DEPENDS "${ASSET}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
            target_sources(${TARGET} ${ACCESS} ${ASSET} ${OUTPUT})
        endforeach()
    endforeach()
endfunction()
