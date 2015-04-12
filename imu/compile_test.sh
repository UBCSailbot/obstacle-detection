clear; clear; g++ -std=c++11 -c imu_data.cpp imu_processor.cpp test_imu_processor.cpp
g++ -o test_imu_proc imu_data.o imu_processor.o test_imu_processor.o

