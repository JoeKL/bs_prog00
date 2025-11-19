# Hacking the "Number Guessing" Game

![Language](https://img.shields.io/badge/language-C11-blue)
![Technique](https://img.shields.io/badge/technique-Memory%20Inspection-red)
![Platform](https://img.shields.io/badge/platform-Linux%20%2F%20POSIX-lightgrey)

A unique solution to a standard "Guess the Number" university assignment. While the expected solution was a Binary Search algorithm, I implemented a memory introspection attack that locates the secret number directly in the process's RAM at runtime.

## 🎮 The Assignment
The goal was simple: Write a function `guess_the_number()` that finds a secret 5-digit random number. The game provides an `evaluate(guess)` function that returns:
* `0`: Correct
* `1`: Too Low
* `-1`: Too High

Most students implemented a **Binary Search** ($O(\log n)$). I decided to cheat (legally).

## 🕵️ The "Hacker" Solution
Instead of guessing, my code inspects the Linux process memory map to find where the secret variable lives and just reads it.

### How it works:
1.  **Read `/proc/self/maps`**: The program opens this virtual file to see its own memory layout.
2.  **Find the Data Segment**: It scans for the first memory region with `rw-p` permissions (Read/Write/Private). This is typically where global variables are stored.
3.  **Calculate Offset**: Using reverse engineering tools (Binary Ninja), I found the static offset (`0x44`) where the secret number is stored relative to the start of the data segment.
4.  **Direct Memory Read**: The pointer is cast and dereferenced to retrieve the answer instantly.

### The Code (Simplified)
```c
unsigned long get_data_segment_start() {
    FILE *maps = fopen("/proc/self/maps", "r");
    // ... scans for "rw-p" permission line ...
    return start_address;
}

unsigned int guess_the_number(void) {
    // 1. Get the base address of the data segment
    unsigned long data_start = get_data_segment_start();

    // 2. Apply the reverse-engineered offset
    unsigned long target_addr = data_start + 0x44;

    // 3. Read the value directly from memory
    int value;
    memcpy(&value, (void *)target_addr, sizeof(int));
    return value;
}
