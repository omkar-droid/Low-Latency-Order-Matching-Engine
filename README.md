# ⚡ Low-Latency Order Matching Engine

A high-performance order matching engine written in **C++11**, optimized for sub-15μs execution latency. Built with a focus on **real-time trading**, **low-latency design**, and **systems-level optimizations**, this engine simulates a modern exchange-style matching core for **limit**, **market**, and **IOC** (Immediate or Cancel) orders.

---

## 🚀 Features

- 🧠 **Matching Algorithms**: Supports Limit, Market, and IOC order types
- ⚙️ **In-Place STL Containers**: Avoids dynamic allocations during runtime
- 🧵 **Multithreaded Ready**: Core engine designed for parallel dispatch
- 💽 **Pre-Allocated Memory Pools**: Zero heap allocations in critical path
- 🧪 **Custom Benchmarks**: Microsecond-level latency tracking using `chrono` and `perf`
- 🖧 **Simulated Market Data Ingestion**: Easily extensible to real TCP/UDP feeds

---

## 🔧 Architecture Overview

- **Order Book**: Dual sorted containers for bid and ask sides
- **Matching Core**: Executes matching logic on incoming orders with priority queues
- **Latency Profiling**: Integrated instrumentation for end-to-end latency measurements
- **Extensibility**: Modular interfaces for adding exchange connectivity or REST/gRPC APIs

---

## 🖥️ Technologies Used

| Component        | Tech Stack          |
|------------------|---------------------|
| Language         | C++11 (STL, Custom Structs) |
| Build Tool       | CMake               |
| OS Optimization  | Linux (epoll, real-time scheduling, CPU pinning) |
| Benchmarking     | `perf`, `chrono`, custom tooling |

---

## 📈 Performance

| Metric                   | Result                     |
|--------------------------|----------------------------|
| Avg Matching Latency     | **< 15μs**                 |
| Throughput               | **100K+ orders/sec**       |
| Allocation Count         | **Zero in hot path**       |
| Memory Usage             | Bounded with preallocation |

---

## 🛠️ Setup & Build

```bash
# Clone the repo
git clone https://github.com/omkar-droid/Low-Latency-Order-Matching-Engine.git
cd Low-Latency-Order-Matching-Engine

# Build with CMake
mkdir build && cd build
cmake ..
make
