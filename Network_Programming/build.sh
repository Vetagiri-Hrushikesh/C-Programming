froot=`pwd`/Server
cd $froot

rm -rf output

# g++   -I./Common -o MaiCommServer  -pthread -Wwrite-strings ./Server/serverTh.cpp ./Server/main.cpp ./Common/common.cpp

# g++   -I./Common -o client  -pthread -Wwrite-strings \
# 							./Client/webClient.cpp    \
# 							./Common/common.cpp


g++ -I./Common -o server -pthread -Wwrite-strings \
./Server/serverTh.cpp \
./Server/main.cpp \
./Common/common.cpp 

mkdir output