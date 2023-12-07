include(GenerateExportHeader)


add_library(statement 
  invoice.cpp  
  statement.cpp
  performance.cpp
  play.cpp
  genre.cpp
  util.cpp
  )

add_library(statement::statement ALIAS statement)

target_link_libraries(statement PRIVATE 
  myproject_options
  myproject_warnings
  nlohmann_json::nlohmann_json
  )

target_include_directories(statement ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(statement PUBLIC cxx_std_20)

set_target_properties(
  statement
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(statement EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/myproject/statement_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(statement PUBLIC STATEMENT_STATIC_DEFINE)
endif()