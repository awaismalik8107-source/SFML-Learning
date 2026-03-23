cmake_minimum_required(VERSION 3.10)
project(MySFMLApp VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML 3 — NO COMPONENTS argument
find_package(SFML 3 REQUIRED)

# Create executable
add_executable(sfml_app main.cpp)

# Link SFML 3 imported targets
target_link_libraries(sfml_app PRIVATE sfml3::graphics sfml3::window sfml3::system)
