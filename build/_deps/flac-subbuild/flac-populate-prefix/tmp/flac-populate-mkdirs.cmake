# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-src"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-build"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/tmp"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/src/flac-populate-stamp"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/src"
  "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/src/flac-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/src/flac-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jjthu/Downloads/COMPUTER SCIENCE/NON_SCHOOL/cmake projects/sfml-multiple-windows/build/_deps/flac-subbuild/flac-populate-prefix/src/flac-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
