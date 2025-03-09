from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

class MyProjectConan(ConanFile):
    name = "test"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "argtable3/3.2.2", "popt/1.16"
    generators = "CMakeToolchain", "CMakeDeps"
    exports_sources = "src/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    def package_info(self):
        self.cpp_info.libs = ("test")