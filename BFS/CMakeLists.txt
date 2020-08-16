project(DFS-examples)

#add_compile_options(-std=c++11)
#aux_source_directory(. single_file_examples)	
set(single_file_examples
BFSexample
  )
  include_directories(
  	  ${CMAKE_SOURCE_DIR}/common
  )
foreach(example ${single_file_examples})
    add_executable(${example}  "${example}.cpp")
    #target_link_libraries(${example} PRIVATE torrent-rasterbar)
endforeach(example)

#target_link_libraries(client_test PRIVATE torrent-rasterbar)


