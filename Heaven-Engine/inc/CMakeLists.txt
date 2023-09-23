project(EngineHeaders LANGUAGES C CXX)

#Grab all header files
file(GLOB_RECURSE ENGHEADER
engine/*.h
engine/*.hpp)

file(GLOB_RECURSE OBJHEADER
gameObjs/*.h
gameObjs/*.hpp)

file(GLOB_RECURSE GLADHEADER
glad/*.h
glad/*.hpp)

file(GLOB_RECURSE ORTHOHEADER
orthoCam/*.h
orthoCam/*.hpp)

file(GLOB_RECURSE RESHEADER
resourceSys/*.h
resourceSys/*.hpp)

file(GLOB_RECURSE WINHEADER
window/*.h
window/*.hpp)

add_library(EngineHeader ${ENGHEADER} ${OBJHEADER} ${GLADHEADER} ${ORTHOHEADER} ${RESHEADER} ${WINHEADER})