aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Editor SOURCESRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Programs SOURCESRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Runtime SOURCESRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Runtime/CoreObject SOURCESRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty SOURCESRCS)

add_library(Source ${SOURCESRCS})