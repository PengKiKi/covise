MACRO(USE_OPENSCENARIO)
set(OPT "")
if ("${ARGN}" STREQUAL "optional")
    set(OPT "optional")
endif()

if(NOT COVISE_BUILD_DRIVINGSIM)
    if (NOT "${OPT}" STREQUAL "optional")
        return()
    endif()
else()
    if (NOT OPENSCENARIO_USED)
        set(OPENSCENARIO_USED TRUE)

        use_proj4(${OPT})
        use_xercesc(${OPT})
        use_boost(${OPT})

        set(EXTRA_LIBS ${EXTRA_LIBS} coOpenScenario)
        include_directories(${COVISEDIR}/src/OpenCOVER/DrivingSim)
    endif()
endif()
ENDMACRO(USE_OPENSCENARIO)
