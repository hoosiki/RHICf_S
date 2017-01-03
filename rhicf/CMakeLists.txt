#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(rhicf)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available Vis drivers by default
# You can set WITH_GEANT4_VIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_VIS "Build example with Geant4 Vis drivers" ON)
if(WITH_GEANT4_VIS)
  find_package(Geant4 REQUIRED gdml vis_all)
else()
  find_package(Geant4 REQUIRED gdml)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT QUIET)
if(NOT ROOT_FOUND)
  message(STATUS "G4 Examples: ROOT package not found. --> rhicf disabled")
  return()
endif()

#----------------------------------------------------------------------------
# Find HepMC
set(HEPMC_INCLUDE_DIR $ENV{HEPMC_INCLUDE})
set(HEPMC_LIBRARY $ENV{HEPMC_LIBRARY})

include_directories(${HEPMC_INCLUDE_DIR})
file(GLOB hepmc ${HEPMC_LIBRARY}/libHepMC.so)

#----------------------------------------------------------------------------
# Find BOOST
set (BOOST_INCLUDEDIR $ENV{BOOST_INCLUDE})
set (BOOST_LIBRARYDIR $ENV{BOOST_LIBRARY})
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)
find_package (Boost REQUIRED COMPONENTS system filesystem timer random program_options)
if(NOT Boost_FOUND)
  message(STATUS "RHICF: BOOST package not found. --> rhicf disabled")
  return()
endif()

#----------------------------------------------------------------------------
# Find Pythia8 (8.215)
#find_package(Pythia8 REQUIRED)
set(PYTHIA8_INCLUDE_DIR $ENV{PYTHIA8_INCLUDE})
set(PYTHIA8PLUGINS_INCLUDE_DIR $ENV{PYTHIA8_INCLUDE})
set(PYTHIA8_LIBRARY_DIR $ENV{PYTHIA8_LIBRARY})

find_path(PYTHIA8_INCLUDE_DIR
          NAMES Pythia.h Pythia8/Pythia.h
	  PATH_SUFFIXES include
          DOC "Specify the directory containing Pythia.h.")

find_library(PYTHIA8_LIBRARY
             NAMES libpythia8.so libpythia8.a
             PATHS ${PYTHIA8_LIBRARY_DIR}
             DOC "Specify the Pythia8 library here.")

foreach(_lib PYTHIA8_LIBRARY)
if(${_lib})
	set(PYTHIA8_LIBRARIES ${PYTHIA8_LIBRARIES} ${${_lib}})
endif()
endforeach()

set(PYTHIA8_INCLUDE_DIRS ${PYTHIA8_INCLUDE_DIR} ${PYTHIA8PLUGINS_INCLUDE_DIR} )
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8 PYTHIA8_INCLUDES_DIRS PYTHIA8_LIBRARIES)

#----------------------------------------------------------------------------
# Find RHICf library
set(RHICF_TOP $ENV{RHICF_TOP})
set(RHICF_LIB $ENV{RHICF_LIB})

include_directories(${RHICF_LIB})
file(GLOB rhicflib ${RHICF_LIB}/libRHICfEvent.so)
message("RHICf library: ${rhicflib}")

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${ROOT_INCLUDE_DIR}
                    ${Geant4_INCLUDE_DIR}
		    ${HEPMC_INCLUDE_DIR}
		    ${Boost_INCLUDE_DIR}
		    ${PYTHIA8_INCLUDE_DIRS}
		    ${RHICF_TOP})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(rhicf rhicf.cc ${sources} ${headers})
target_link_libraries(rhicf ${Geant4_LIBRARIES} ${PYTHIA8_LIBRARIES} ${hepmc} ${Boost_LIBRARIES} ${ROOT_LIBRARIES} ${rhicflib})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build rhicf. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(rhicf_SCRIPTS
    crmc.param input.dat
  )

foreach(_script ${rhicf_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Add program to the project targets
# (this avoids the need of typing the program name after make)
#
#add_custom_target(rhicf DEPENDS)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS rhicf DESTINATION bin)
