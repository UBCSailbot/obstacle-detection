g++ -std=c++11 -c test_imu_stream.cpp imu_data.cpp imu_processor.cpp imu.cpp serial.cpp
g++ -std=c++11 -o test_imu_stream imu_processor.o imu_data.o imu.o test_imu_stream.o serial.o
