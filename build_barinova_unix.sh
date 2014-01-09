cd ObjectDetection/ObjectDetection/
rm -rf build
mkdir build
cd build

cmake ..
make

cp object_detection ../../../object_detection
cd ../../../
