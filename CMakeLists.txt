project(hermes_tutorial)
	cmake_minimum_required(VERSION 2.6)

	set(CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake)
        include(CommonTargetProperties)
	
	# --- OPTIONS
	#
	# Where to look for the static libraries (may be overriden by CMake.vars).
	set(HERMES_DIRECTORY "/usr/local/lib")
	set(HERMES_INCLUDE_PATH "/usr/local/include")
	set(DEP_INCLUDE_PATHS "/usr/local/include")

	# Trilinos
	# Enable support for Trilinos solvers.
	set(WITH_TRILINOS           NO)
				
	# Experimental
	set(WITH_ZOLTAN             NO)
	# If MPI is enabled, the MPI library installed on the system should be found by 
		# CMake automatically. If the found library doesn't match the one used to compile the
		# particular MPI-dependent package, the other two options should be used to specify it.
		#
		set(WITH_MPI                NO)
		# set(MPI_LIBRARIES         -lmpi)
		# set(MPI_INCLUDE_PATH      /usr/include/openmpi

	# Include debugging symbols.
	set(DEBUG_VERSION           YES)
	
	# Allow to override the default values in CMake.vars:
	include(CMake.vars OPTIONAL)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			# Disable all warnings and turn on only important ones:
			set(CMAKE_CXX_FLAGS "-w ${CMAKE_CXX_FLAGS}")
			set(CMAKE_CXX_FLAGS "-Wuninitialized -Wvla -Wsign-compare ${CMAKE_CXX_FLAGS}")

			set(RELEASE_FLAGS "-DNDEBUG -O3")
			set(DEBUG_FLAGS   "-g")
	endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

	# Enabling multiprocessor build on MSVC
	if(MSVC)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP") 
	endif(MSVC)
	
    include_directories("${PTHREAD_ROOT}/include")
	find_package(PTHREAD REQUIRED)

	if(WITH_TRILINOS)
		find_package(TRILINOS REQUIRED)
		include_directories(${TRILINOS_INCLUDE_DIR})
	endif(WITH_TRILINOS)
	
	if(WITH_MPI)
		if(NOT MPI_INCLUDE_PATH)
			find_package(MPI REQUIRED)
		endif(NOT MPI_INCLUDE_PATH)
		include_directories(${MPI_INCLUDE_PATH})
	endif(WITH_MPI)
	
	set(HERMES2D_INCLUDE_PATH ${HERMES_INCLUDE_PATH}/hermes2d)
	set(HERMES_COMMON_INCLUDE_PATH ${HERMES_INCLUDE_PATH}/hermes_common)
	
	find_package(HERMES_COMMON REQUIRED)

	include_directories(${HERMES_COMMON_INCLUDE_PATH})
	include_directories(${HERMES2D_INCLUDE_PATH})
	include_directories(${DEP_INCLUDE_PATHS})

  # --- SUBFOLDERS WITH TUTORIAL TOPICS
  #
  # Linear problems.
  add_subdirectory(A-linear)

  # Nonlinear problems.
  add_subdirectory(B-nonlinear)

  # Time-dependent problems.
  add_subdirectory(C-transient)

  # Adaptivity.
  add_subdirectory(D-adaptivity)

  # FVM and DG.
  add_subdirectory(E-fvm-and-dg)

  # Using Trilinos.
  if(WITH_TRILINOS)
    add_subdirectory(F-trilinos)
  endif(WITH_TRILINOS)

  # Miscellaneous techniques.
  add_subdirectory(G-miscellaneous)

