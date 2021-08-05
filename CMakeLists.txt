set(_srcs
  src/FileInstallActivator.cpp
 # src/FileInstall.cpp
)


set(_private_headers
)

set(_public_headers
  #include/cppmicroservices/shellservice/FileInstall.h
)

set(_resources
  manifest.json
)

add_definitions(-DSTANDALONE=0 -DUSE_INTERFACE=1)

usMacroCreateBundle(FileInstall
  VERSION "0.1.0"
  DEPENDS Framework
  PUBLIC_HEADERS ${_public_headers}
  PRIVATE_HEADERS ${_private_headers}
  SOURCES ${_srcs}
  RESOURCES ${_resources}
)

