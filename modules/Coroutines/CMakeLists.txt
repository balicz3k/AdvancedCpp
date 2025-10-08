cmake_minimum_required(VERSION 3.16)

add_executable(Coroutines
	main.cpp
)

if (COMMAND enable_target_warnings)
	enable_target_warnings(Coroutines)
endif()
