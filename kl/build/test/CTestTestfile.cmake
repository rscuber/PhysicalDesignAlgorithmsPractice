# CMake generated Testfile for 
# Source directory: /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test
# Build directory: /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[google_test]=] "/Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test/kl_unit_test")
set_tests_properties([=[google_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test/CMakeLists.txt;37;add_test;/Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
