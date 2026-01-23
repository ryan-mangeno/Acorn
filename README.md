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
brew install molten-vk vulkan-loader vulkan-headers vulkan-tools
```

### 3. Make and Run Build
```bash
cmake -B build
cmake --build build
```

### 5. Set Vulkan environment variables ( I need to abstract this better )

MoltenVK requires Vulkan loader headers and libraries to be visible. Add these exports in your shell:

```bash
sudo mkdir -p /opt/homebrew/share/vulkan/icd.d


sudo ln -sf \
"$(brew list molten-vk | grep MoltenVK_icd.json)" \
/opt/homebrew/share/vulkan/icd.d/MoltenVK_icd.json
```


