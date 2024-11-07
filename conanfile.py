import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy

class MyConanFile(ConanFile):
  name = "dreich"
  version = "1.0"
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps", "CMakeToolchain"
  exports_sources = "*"

  default_options = {
    "fmt/*:header_only": True,
  }

  def requirements(self):
    self.requires("sdl/2.30.8")
    self.requires("catch2/3.7.1")
    self.requires("spdlog/1.13.0")

    self.requires("cxxopts/3.1.1")
    self.requires("pugixml/1.13")
    self.requires("yaml-cpp/0.8.0")
    self.requires("stb/cci.20220909")
    self.requires("zlib/1.2.11")

    self.requires("glad/0.1.36")
    self.requires("glm/cci.20230113")
    self.requires("imgui/cci.20230105+1.89.2.docking")

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def deploy(self):
    copy(self, "*", src=self.package_folder, dst=self.deploy_folder)

  def layout(self):
    cmake_layout(self)
