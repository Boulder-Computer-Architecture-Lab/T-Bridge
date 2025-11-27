# T-Bridge

**T-Bridge** is a fast, lightweight cache simulator designed to generate DRAM traces from Load/Store instruction traces. It bridges the gap between CPU instruction streams and memory system analysis by filtering memory accesses through a configurable cache.

## 🚀 Features

* **DRAM Trace Generation**: Filters CPU Load/Store instructions to produce accurate traces of main memory (DRAM) accesses.
* **Configurable Cache Parameters**: Customize cache size, associativity, block size, and more via the configuration file.
* **Trace Support**: Designed to handle standard Load/Store instruction traces.
* **High Performance**: Written in C++ for efficient simulation of large trace files.

## 🛠 Prerequisites

* **C++ Compiler**: GCC (g++) or Clang with C++11/17 support.
* **CMake**: Version 3.10 or higher.
* **Make**: Standard build tool.

## 🔨 Build Instructions

You can build the project using the provided helper script or manually via CMake.

### Clone and Initialize
Since this project uses external libraries, you must initialize the submodules after cloning:

```bash
git clone https://github.com/Boulder-Computer-Architecture-Lab/T-Bridge.git
cd T-Bridge
git submodule update --init --recursive
```

### Option 1: Quick Build
Use the provided shell script to automate the build process:
```bash
chmod +x quick_build.sh
./quick_build.sh
```

### Option 2: Manual CMake build
Manually build the project using cmake:
```bash
mkdir build
cd build
cmake ..
make
cp bin/CacheSimulator ../.
cd ..
```

## 🎯 Roadmap

We are actively working on extending and improving T-Bridge.

### High Priority:
- [ ] **Improve Example Trace**: Improve the example trace to be more complex.
- [ ] **Implement Unit Tests**: Implement unit tests that check the proper functionality of the simulator.
- [ ] **Modular Prefetching Framework**: A flexible interface to support both standard and custom hardware prefetchers. This allows researchers to prototype new prefetching algorithms and generate realistic DRAM traffic patterns.

### Medium Priority:
- [ ] **Module Replacement Policy Framework**: A flexible interface to support both standard and custom replacement policies. This allows researchers to prototype new replacement policies and generate realistic DRAM traffic patterns.
- [ ] **Multi-Core Support**: Handling interleaved instruction streams from multiple CPU cores to simulate shared cache contention and coherency traffic.
- [ ] **Parallelism Support**: Investigate parallelism for even faster processing.

<!-- 
## 📚 Reference

The initial release of T-Bridge is described in the following [paper](...):
> Authors
> "PaperName"
> Journal.

If you use T-Bridge in your research, please cite the following paper:

```bibtex
@article{paper_name,
  author  = {Lastname, Firstname and Lastname, Firstname},
  title   = {Title},
  journal = {Journal},
  year    = {Year},
  volume  = {},
  number  = {},
  pages   = {},
  doi     = {}
}
```
-->