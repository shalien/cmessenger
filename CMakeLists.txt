cmake_minimum_required(VERSION 3.25)
project(cmessenger C)

set(CMAKE_C_STANDARD 23)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_executable(cmessenger src/main.c src/log/siren.c src/client/client.c src/client/client.h src/server/server.c src/server/server.h src/utils/cmesseger_common.h src/main.h src/utils/sem_utils.c src/utils/sem_utils.h src/utils/thread_initializer.h src/utils/shared_memory_utils.c src/utils/shared_memory_utils.h)

target_link_libraries(cmessenger Threads::Threads)
