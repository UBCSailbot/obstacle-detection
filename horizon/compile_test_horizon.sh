g++ -std=c++11 -g -c test_horizon.cpp ../imu/imu_data.cpp ../imu/imu_processor.cpp Horizon.cpp
echo "done compiling"
g++ -std=c++11 -g -o test_horizon test_horizon.o imu_processor.o imu_data.o Horizon.o -I/usr/include/opencv -lopencv_core -lopencv_highgui
echo "done linking"