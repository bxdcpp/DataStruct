project(Programming)

#add_compile_options(-std=c++11)
#aux_source_directory(. single_file_examples)	
set(SRC
smart_ptr.h
test_virtual_class.h
test_operator_overload.h
main.cpp
  )
  include_directories(
     ${CMAKE_CURRENT_SOURCE_DIR}
  	  ${CMAKE_SOURCE_DIR}/common
  )
  message( status ${CMAKE_CURRENT_SOURCE_DIR})

  add_executable(${PROJECT_NAME}  ${SRC})


#target_link_libraries(client_test PRIVATE torrent-rasterbar)


