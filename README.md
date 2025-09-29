 # CS 3503 Assignment 2- Advanced Data Representation
  ## Author
 Augustas Jasinskas
  ## Description
 My implementation of Owl Tech’s Advanced Data Representation Utility was developed on C through Clion. It is able to utilize direct mapping functions for fast conversions through the use of bit patterns, as well as functions that showcase sign magnitude, one complement, and two complement signed representations of negative numbers. there are 6 functions that         directly do this: oct_to_bin, oct_to_hex, hex_to_bin, to_sign_magnitude, to_ones_complement, and to_twos_complement.

 My main.c file then reads, parses, and runs each tests case in the given a2test file. each test has a pass/fail result.
  ## Build Instructions
  gcc-o convert convert.c main.c ./convert

  ## Test Results
  51/51 Tests Passed.
 
  ## Notes
  I decided to implement a couple of helper functions in convert.c because of some necessary but repeated lines of code, to allow for better readability and prevent mistakes. Understanding the differences between the 3 forms of negative number representation and how they differ from one another was a challenge for me which made me take a good bit of time on those functions.
