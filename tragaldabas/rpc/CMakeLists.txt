# Create a library called "libTraRPC" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES 
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
#put here all directories where header files are located
${ENSARROOT_SOURCE_DIR}/tragaldabas/data
${ENSARROOT_SOURCE_DIR}/tragaldabas/gen
${ENSARROOT_SOURCE_DIR}/tragaldabas/geometry 
${ENSARROOT_SOURCE_DIR}/tragaldabas/passive
${ENSARROOT_SOURCE_DIR}/tragaldabas/rpc
${ENSARROOT_SOURCE_DIR}/tragaldabas/db
${ENSARROOT_SOURCE_DIR}/ensarbase
${ENSARROOT_SOURCE_DIR}/ensardata
${BASE_INCLUDE_DIRECTORIES}   
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
TraRPC.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF RPCLinkDef.h)
set(LIBRARY_NAME TraRPC)
set(DEPENDENCIES
    EnsarBase EnsarData MCStack)

GENERATE_LIBRARY()

