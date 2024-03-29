cmake_minimum_required(VERSION 3.16)
project(fft_gkr)
include_directories(include .)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -O3")
#we enable optimization by default, you can remove -O3 for debug purpose
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -lstdc++ -Wall -march=native -faligned-new -O3")

add_executable(fft_gkr src/VPD/fft_circuit_GKR.cpp src/linear_gkr/prime_field.cpp src/linear_gkr/polynomial.cpp)
add_executable(linear_code src/encode_test.cpp src/linear_code/linear_code_encode.cpp src/linear_code/expander.cpp src/linear_gkr/prime_field.cpp src/infrastructure/RS_polynomial.cpp src/infrastructure/merkle_tree.cpp src/infrastructure/utility.cpp)
add_executable(linearPC src/VPD/linearPC_test.cpp src/linear_code/linear_code_encode.cpp src/linear_code/expander.cpp src/VPD/linearPC.cpp src/infrastructure/RS_polynomial.cpp src/infrastructure/merkle_tree.cpp src/infrastructure/utility.cpp src/VPD/fri.cpp src/VPD/vpd_prover.cpp src/VPD/vpd_verifier.cpp src/linear_gkr/verifier.cpp src/linear_gkr/prime_field.cpp src/linear_gkr/prover.cpp src/linear_gkr/polynomial.cpp src/poly_commitment/poly_commit.cpp)

target_link_libraries(linear_code -Llib -lflo-shani -lXKCP -lgmp)
target_link_libraries(linearPC -Llib -lflo-shani -lXKCP -lgmp)
