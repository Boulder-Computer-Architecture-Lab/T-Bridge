# T-Bridge

**T-Bridge** is a fast cache simulator designed to generate main memory access traces from Load/Store instruction traces. It bridges the gap between functional instrumentation and DRAM simulation

## Build Instructions

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

## Roadmap

We are actively working on extending and improving T-Bridge.

### High Priority:
- [ ] **Improve Example Trace**: Improve the example trace to be more complex.
- [ ] **Implement Unit Tests**: Implement unit tests that check the proper functionality of the simulator.
- [ ] **Modular Hardware Prefetching Interface**: A flexible interface to support both standard and custom hardware prefetchers. This allows researchers to prototype new prefetching algorithms and generate realistic DRAM traffic patterns.
- [ ] **Modular Replacement Policy Interface**: A flexible interface to support both standard and custom replacement policies. This allows researchers to prototype new replacement policies and generate realistic DRAM traffic patterns.

### Medium Priority:
- [ ] **Cache Hierarchy and Coherency Support**: Support for a multi-level cache hierarchy with coherency support.
- [ ] **Multi-Core Support**: Handling interleaved instruction streams from multiple CPU cores to simulate shared cache contention and coherency traffic.
- [ ] **Parallelism Support**: Investigate parallelism for even faster processing.

<!-- 
## Reference

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
