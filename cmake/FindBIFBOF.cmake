# - Find BIFBOF
# Find the BIFBOF includes and library
#
#  BIFBOF_INCLUDE_DIR - Where to find BIFBOF includes
#  BIFBOF_LIBRARIES   - List of libraries when using BIFBOF
#  BIFBOF_FOUND       - True if BIFBOF was found

IF(BIFBOF_INCLUDE_DIR)
  SET(BIFBOF_FIND_QUIETLY TRUE)
ENDIF(BIFBOF_INCLUDE_DIR)

FIND_PATH(BIFBOF_INCLUDE_DIR "hdmproto.h"
  PATHS
  $ENV{BIFBOF_HOME}/include
  $ENV{EXTERNLIBS}/BIFBOF/include
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  DOC "BIFBOF - Headers"
)

SET(BIFBOF_NAMES dsio)
SET(BIFBOF_DBG_NAMES dsio_md_d)

FIND_LIBRARY(BIFBOF_LIBRARY NAMES ${BIFBOF_NAMES}
  PATHS
  $ENV{BIFBOF_HOME}
  $ENV{EXTERNLIBS}/BIFBOF
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  PATH_SUFFIXES lib lib64
  DOC "BIFBOF - Library"
)

INCLUDE(FindPackageHandleStandardArgs)

IF(MSVC)
  # VisualStudio needs a debug version
  FIND_LIBRARY(BIFBOF_LIBRARY_DEBUG NAMES ${BIFBOF_DBG_NAMES}
    PATHS
    $ENV{BIFBOF_HOME}
    $ENV{EXTERNLIBS}/BIFBOF
    PATH_SUFFIXES lib lib64
    DOC "BIFBOF - Library (Debug)"
  )
  
  IF(BIFBOF_LIBRARY_DEBUG AND BIFBOF_LIBRARY)
    SET(BIFBOF_LIBRARIES optimized ${BIFBOF_LIBRARY} debug ${BIFBOF_LIBRARY_DEBUG})
  ENDIF(BIFBOF_LIBRARY_DEBUG AND BIFBOF_LIBRARY)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(BIFBOF DEFAULT_MSG BIFBOF_LIBRARY BIFBOF_LIBRARY_DEBUG BIFBOF_INCLUDE_DIR)

  MARK_AS_ADVANCED(BIFBOF_LIBRARY BIFBOF_LIBRARY_DEBUG BIFBOF_INCLUDE_DIR)
  
ELSE(MSVC)
  # rest of the world
  SET(BIFBOF_LIBRARIES ${BIFBOF_LIBRARY})

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(BIFBOF DEFAULT_MSG BIFBOF_LIBRARY BIFBOF_INCLUDE_DIR)
  
  MARK_AS_ADVANCED(BIFBOF_LIBRARY BIFBOF_INCLUDE_DIR)
  
ENDIF(MSVC)

IF(BIFBOF_FOUND)
  SET(BIFBOF_INCLUDE_DIRS ${BIFBOF_INCLUDE_DIR})
ENDIF(BIFBOF_FOUND)