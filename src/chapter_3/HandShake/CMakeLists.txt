# TODO(ralntdir): Make changes so it works in Linux!

cmake_minimum_required(VERSION 3.7.1)
set (Recipe_Name "3_0_DeviceHandshake")

# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDk path can be specified manually
# This is helpful to test the build on various Vulkan versions.
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if(AUTO_LOCATE_VULKAN)

	message(STATUS "Attempting auto locate Vulkan using CMake......")

	# Find Vulkan Path using CMake's Vulkan Module
	# This will return Boolean 'Vulkan_FOUND' indicating
	# the status of find and success(ON) or fail(OFF).
	# Include directory path - 'Vulkan_INCLUDE_DIRS'
	# and 'Vulkan_LIBRARY' with required libraries.
	find_package(Vulkan)

	# Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
	if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
		set (VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
		STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
	endif()

	if(NOT Vulkan_FOUND)
		# CMake may fail to locate the libraries but could be able to
		# provide some path in Vulkan SDK include directory variable
		# 'Vulkan_INCLUDE_DIRS', try to extract path from this.
		
		message(STATUS "Failed to locate Vulkan SDK, retrying again...")

		# Check if Vulkan path is valid, if not switch to manual mode.
		if (EXISTS "${VULKAN_PATH}")
			message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
		else()
			message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
			message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
			return()
		endif()
	endif()
else()
	message(STATUS "Attempting to locate Vulkan SDK using manual path......")
	set(VULKAN_SDK "/home/ivan/desarrollo/vulkan/VulkanSDK")
	set(VULKAN_VERSION "1.0.65.0")
	set(VULKAN_PATH "${VULKAN_SDK/${VULKAN_VERSION}")
	message(STATUS "Using manual specified path: ${VULKAN_PATH}")

	# Check if manual set path exists
	if(NOT EXISTS "${VULKAN_PATH}")
		message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
		return()
	endif()
endif()

# Specify a suitable project name
project(${Recipe_Name})