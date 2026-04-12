# C++ Explorations and Projects

A comprehensive collection of C++ implementations encompassing data structures, multithreading, socket programming, and active projects like the **Position Engine**.

## 🚀 Projects

### Position Engine (`positionEngine.cpp`)
A C++ command-line application that tracks trading positions, calculating net quantity, average price, realized PnL (Profit and Loss), and unrealized PnL based on trade executions and market price updates.

#### Features
- **Side Support**: Tracks both `BUY` and `SELL` fills.
- **PnL Calculation**: Calculates realized and unrealized PnL dynamically based on the recent fills and market prices.
- **Interactive CLI**: Takes standard input commands to process market events continuously.

#### Building and Running
```bash
g++ -std=c++17 -Wall -Wextra -O2 positionEngine.cpp -o positionEngine
./positionEngine
```

#### Commands
- `FILL <BUY|SELL> <QTY> <PRICE>`: Processes a trade execution.
- `PRICE <MARKET_PRICE>`: Updates the current market price of the asset.
- `PRINT`: Outputs the current status of the position.

## 🛠 Features and Concepts

This repository also contains various implementations showcasing modern C++ paradigms:

### Data Structures & Algorithms
- **`linkedlist.cpp`**: Basic linked list implementation.
- **`graph.cpp`**: Graph data structures and algorithms using adjacency matrices.
- **`tree.cpp`**: Binary tree implementations.
- **`lrucache.cpp`**: LRU (Least Recently Used) cache implementation using doubly linked list and map.
- **`dp.cpp`**: Dynamic programming exercises and algorithms.

### Concurrency & Multithreading
- **`threadpool.cpp`**: An efficient multithreaded thread pool utilizing `std::thread`, `std::mutex`, and `std::condition_variable`.
- **`lockfree_queue.cpp`**: Implementation of a lock-free ring buffer queue leveraging `std::atomic` operations.
- **`producer_consumer_1.cpp`**: Classical producer-consumer pattern implementation using `std::binary_semaphore`.
- **`multithreading.cpp` / `logger.cpp`**: Further explorations in synchronizing operations and logging across threads.

### Network Programming
- **`socketServer.cpp` & `socketClient.cpp`**: Client-Server socket programming utilizing `sys/socket.h` and raw socket APIs with threading support.

### Advanced C++
- **`isprime_compiletime.cpp`**: Compile-time prime verification using templates and `constexpr`.
- **`unique_ptr.cpp`**: Demonstrations of modern C++ smart pointers and memory management.
- **`Event.cpp` / `clock.cpp`**: Event handling and system time tracking.

## 📝 Miscellaneous
- **Python ML/LLM Scripts**: `multimodalllm.py`, `script.py`. Contains experimental setups alongside C++ logic.
- **Practice Specific**: Scripts assigned sequentially (`a1.cpp` to `a4.cpp`, `p1`, etc.).

---

**Note:** Ensure you're compiling implementations requiring C++20 standard paradigms (like semaphores) with the `-std=c++20` or equivalent compiler flags.
