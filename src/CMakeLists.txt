set(sources
    main.cpp)

add_executable(header-dump ${sources})

if (MSVC)
    target_compile_options(header-dump PRIVATE /W4 /EHsc)
else ()
    target_compile_options(header-dump PRIVATE -Wall -Wextra -pedantic)
endif ()
