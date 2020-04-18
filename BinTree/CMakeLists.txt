project(BTree-examples)


#aux_source_directory(. single_file_examples)	
set(single_file_examples
BinTree
BinTree2
BinTree3
  )

foreach(example ${single_file_examples})
    add_executable(${example} "${example}.cpp")
    #target_link_libraries(${example} PRIVATE torrent-rasterbar)
endforeach(example)


