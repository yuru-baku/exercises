add_subdirectory(statement)
add_executable(invoice main.cpp)

target_link_libraries(
  invoice
  PRIVATE myproject::myproject_options
          myproject::myproject_warnings
          statement::statement
          nlohmann_json::nlohmann_json)

target_link_system_libraries(
  invoice
  PRIVATE
          fmt::fmt
          spdlog::spdlog)

target_include_directories(invoice PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
