cmake_minimum_required(VERSION 3.10)
project(myProgram)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


enable_testing()

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

FetchContent_MakeAvailable(googletest)


# Создаем список исходных файлов для библиотеки

# Указываем include-директории для библиотеки


# Создаем основное приложение
add_executable(${PROJECT_NAME} src/main.cpp)

# Связываем приложение с нашей библиотекой

# Создаем исполняемый файл для тестов
add_executable(${PROJECT_NAME}_tests test/tests.cpp)

# Связываем тесты с нашей библиотекой и Google Test
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
 gtest_main
)

# Указываем include-директории для тестов
target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Добавление тестов в тестовый набор
add_test(NAME ${PROJECT_NAME}_Tests COMMAND ${PROJECT_NAME}_tests)