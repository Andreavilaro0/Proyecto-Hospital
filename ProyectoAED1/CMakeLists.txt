# CMakeList.txt: proyecto de CMake para ProyectoAED1, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required(VERSION 3.14)
project(ProyectoAED1)

# Agregue un origen al ejecutable de este proyecto.
set(ProjectTarget ProyectoAED1)
set(ProjectName ProyectoAED1)
set(LibTarget lib) #AEDProfeCMakeLib
set(LibName lib)	
add_executable (${ProjectTarget} "${ProjectName}.cpp" "${ProjectName}.h" "${LibTarget}.h" "${LibTarget}.cpp")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET ProyectoAED1 PROPERTY CXX_STANDARD 20)
#endif()

#target_link_libraries(${ProjectTarget} PUBLIC 
#						".\\lib\\"
#						"..\\out\\"
#						)

#add_subdirectory("lib")
#target_link_libraries(${ProjectTarget} PUBLIC ${LibTarget})

#for Google Test:
enable_testing()

# Descargar Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable( ${ProjectTarget}_test 
				"${ProjectName}_test.cpp"
				"${LibTarget}.h" 
				"${LibTarget}.cpp"
				)
target_link_libraries( ${ProjectTarget}_test	
	GTest::gtest_main
	)

include(GoogleTest)
gtest_discover_tests(${ProjectTarget}_test)

# TODO: Agregue pruebas y destinos de instalación si es necesario.
