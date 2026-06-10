from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake


class ProtonEngineRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("glad/2.0.8")
        self.requires("entt/3.16.0")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")
        self.requires("imgui/1.92.8-docking")
        self.requires("stb/cci.20240531")

    def build_requirements(self):
        self.tool_requires("llvm-toolchain/20.1.0")
        self.tool_requires("cmake/[>=4.2.0]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def layout(self):
        cmake_layout(self)

    def configure(self):
        pass
