# Build Configuration Guide

## Graphics Enhancement Build Options

### Recommended Settings for Best Graphics

```bash
# Windows with Visual Studio
cmake .. -A Win32 \
  -DCMAKE_BUILD_TYPE=Release \
  -DHalfLife_LTO=ON \
  -DHalfLife_ENABLE_GRAPHICS_ENHANCEMENTS=ON \
  -DHalfLife_ENABLE_PERFORMANCE_OPTIMIZATIONS=ON \
  -DCMAKE_INSTALL_PREFIX="path/to/game/mod"
```

### Linux Build with Optimizations

```bash
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=../cmake/LinuxToolchain.cmake \
  -DHalfLife_LTO=ON \
  -DHalfLife_ENABLE_GRAPHICS_ENHANCEMENTS=ON \
  -DHalfLife_ENABLE_PERFORMANCE_OPTIMIZATIONS=ON \
  -DCMAKE_CXX_FLAGS="-march=native -O3" \
  -DCMAKE_INSTALL_PREFIX=~/halflife/mymod
```

## Build Flags Explanation

| Flag | Description | Default |
|------|-------------|---------|
| `HalfLife_LTO` | Link-Time Optimization | ON |
| `HalfLife_ENABLE_GRAPHICS_ENHANCEMENTS` | Graphics improvements | ON |
| `HalfLife_ENABLE_PERFORMANCE_OPTIMIZATIONS` | Performance optimizations | ON |
| `CMAKE_BUILD_TYPE` | Release/Debug build | Release |

## Building Steps

### Step 1: Create Build Directory
```bash
mkdir build
cd build
```

### Step 2: Configure CMake
```bash
cmake .. [options above]
```

### Step 3: Build Project
```bash
cmake --build . --config Release -j$(nproc)
```

### Step 4: Install
```bash
cmake --install .
```

## Compiler Recommendations

### Visual Studio 2022 (Recommended)
- Newer, better optimization support
- Better C++17 support
- Superior diagnostics

### GCC 11+
- Better SIMD support
- Improved vectorization
- Better optimization flags: `-O3 -march=native -flto`

### Clang 14+
- Fast compilation
- Good optimization
- Better error messages

## Performance Tips

1. **Use Release Build**: Always use Release build for best performance
2. **Enable LTO**: Link-Time Optimization provides 5-15% performance improvement
3. **Use Native Architecture**: `-march=native` optimizes for your CPU
4. **Profile Before Optimizing**: Use Performance Profiler to find bottlenecks
5. **Memory Alignment**: Ensure proper memory alignment for SIMD operations

## Troubleshooting Build Issues

### LTO Build Fails
- Make sure you have enough RAM (LTO is memory-intensive)
- Try disabling with `-DHalfLife_LTO=OFF`

### Missing Dependencies
- Install required packages: `g++-multilib`, `libgl1-mesa-dev`
- Check CMake output for specific missing packages

### Slow Build on Linux
- Use `-j$(nproc)` to use all CPU cores
- Consider ccache for faster rebuilds

## Next Steps

After building successfully:
1. Test the mod in-game
2. Check Performance Profiler output
3. Adjust settings based on your system
4. Monitor FPS and GPU usage
