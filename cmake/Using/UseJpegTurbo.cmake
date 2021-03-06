MACRO(USE_JPEGTURBO)
  IF ((NOT JPEGTURBO_FOUND) AND (${ARGC} LESS 1))
    USING_MESSAGE("Skipping because of missing JPEGTURBO")
    RETURN()
  ENDIF((NOT JPEGTURBO_FOUND) AND (${ARGC} LESS 1))
  if (JPEG_USED)
     message("Using JPEGTURBO: conflict cannot use together with JPEG")
     return()
  endif()
  IF(NOT JPEGTURBO_USED AND JPEGTURBO_FOUND)
    SET(JPEGTURBO_USED TRUE)
    INCLUDE_DIRECTORIES(${JPEGTURBO_INCLUDE_DIR})
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${JPEGTURBO_LIBRARY})
  ENDIF()
ENDMACRO(USE_JPEGTURBO)

