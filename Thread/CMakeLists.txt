project(Thread-examples)

set(single_file_examples
ThreadExample
  )

foreach(example ${single_file_examples})
    add_executable(${example} "${example}.cpp")
endforeach(example)


