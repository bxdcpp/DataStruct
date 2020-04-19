project(BTree-examples)

#add_compile_options(-std=c++11)
#aux_source_directory(. single_file_examples)	
set(single_file_examples
BinTree
BinTree2
BinTree3
SortTemplates
SearchExample
  )

foreach(example ${single_file_examples})
    add_executable(${example} "${example}.cpp")
    #target_link_libraries(${example} PRIVATE torrent-rasterbar)
endforeach(example)

add_executable(LeetCodeBinTree
    LeetCodeBinTree.cpp
    LeetCodeBinTree.h
	)
#target_link_libraries(client_test PRIVATE torrent-rasterbar)


