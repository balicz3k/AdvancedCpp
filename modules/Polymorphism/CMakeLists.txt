cmake_minimum_required(VERSION 3.16)

add_executable(Polymorphism
	main.cpp
)

if (COMMAND enable_target_warnings)
	enable_target_warnings(PolymorphismDemo)
endif()
