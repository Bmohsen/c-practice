cmake_minimum_required(VERSION 3.24)
project(SCli VERSION 1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure the vcpkg toolchain is used (via CMakePresets or -DCMAKE_TOOLCHAIN_FILE)
# and manifest mode is enabled. 


# Find and link vcpkg packages
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ftxui       CONFIG REQUIRED)
find_package(unofficial-uwebsockets CONFIG REQUIRED)

# Define the executable with all source files
add_executable(${PROJECT_NAME}
    app.cpp
    src/todo/Todo.cpp
    src/password-manager/pmanager.cpp
 "src/process-list/ProcessList.cpp")

# Include headers from src/
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")


# Link vcpkg-provided library targets
target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_json::nlohmann_json     # JSON for Modern C++:contentReference[oaicite:3]{index=3}
    ftxui::screen                    # FTXUI screen component:contentReference[oaicite:4]{index=4}
    ftxui::dom                       # FTXUI DOM component:contentReference[oaicite:5]{index=5}
    ftxui::component                 # FTXUI component library:contentReference[oaicite:6]{index=6}
    unofficial::uwebsockets::uwebsockets
)
