cmake_minimum_required(VERSION 3.10)
project(ConvexHull)
set (EXE_NAME ConvexHull)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "ConvexInputFiles/Input1.txt")
set (input02 "ConvexInputFiles/Input2.txt")
set (input03 "ConvexInputFiles/Input3.txt")
set (input04 "ConvexInputFiles/Input4.txt")
set (input05 "ConvexInputFiles/Input5.txt")
set (input06 "ConvexInputFiles/Input6.txt")
set (input07 "ConvexInputFiles/Input7.txt")
set (input08 "ConvexInputFiles/Input8.txt")
set (input09 "ConvexInputFiles/Input9.txt")
set (input10 "ConvexInputFiles/Input10.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 input05 input06 input07 input08 input09 input10)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_STANDARD 14)
add_executable(${EXE_NAME} main.cpp Runner.cpp Runner.h)

