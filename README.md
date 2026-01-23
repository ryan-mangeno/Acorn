# Acorn

Acorn is a C++ project using **GLFW**, **ImGui**, **yaml-cpp**, and **Vulkan (MoltenVK)** on **macOS arm64**. It uses CMake for building and manages dependencies via recursive Git submodules.

---

## Requirements (MacOS For Now)

- **CMake >= 3.20**
- **Xcode** (compiler toolchain)
- **Homebrew** (for Vulkan / MoltenVK)
- **Git** (with recursive submodules)


### Notes
- Utilizes Vulkan and C++17, deps will grow

---

## Setup

### 1. Clone the repository with submodules

```bash
git clone --recursive https://github.com/ryan-mangeno/Acorn.git
cd Acorn
```

### 2. Install Deps
```bash
brew install molten-vk vulkan-headers vulkan-loader
```

### 3. Make and Run Build
```bash
cmake -B build
cmake --build build
```

### 5. Set Vulkan environment variables ( I need to abstract this better )

MoltenVK requires Vulkan loader headers and libraries to be visible. Add these exports in your shell:

```bash
# Path to Vulkan SDK (Homebrew)
export VULKAN_SDK=/opt/homebrew/opt/vulkan-loader

# Include Vulkan headers
export CPLUS_INCLUDE_PATH=$VULKAN_SDK/include:$CPLUS_INCLUDE_PATH

# Add Vulkan libraries to linker path
export LIBRARY_PATH=$VULKAN_SDK/lib:$LIBRARY_PATH
export DYLD_LIBRARY_PATH=$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH
```


