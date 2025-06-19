# Chessmaster Challenge

**Quantum Chess Simulator & Tournament Logistics Toolkit**  
A C++ project simulating futuristic Quantum Chess board operations and managing intergalactic chess tournaments using computational geometry and algorithmic analysis.

---

## Overview

In the year 3045, the **Intergalactic Chess Federation (ICF)** adopts a revolutionary twist to traditional chess with *Quantum Chess*. The twist includes a dynamic **n × n board** where each square holds a *quantum state*—a number determining entanglement levels. 

This system also handles **logistics** for the **Galactic Chess Olympics**, including pairing players based on spatial proximity in a 2D plane (space station map).

Led by Dr. Axel Quark, this project includes:
- Quantum row stabilization via sorting
- Total board inversion calculation
- Efficient closest pair detection among space players using Divide & Conquer

---

## Features

-  **Dynamic Board Creation**: Supports matrix sizes up to 1000×1000 with 64-bit integers.
-  **Row Sorting**: Sort each row independently in ascending or descending order.
-  **Inversion Count**: Count total number of global inversions in the matrix using a modified merge sort.
-  **Closest Pair of Players**: Find the pair of points in 2D with the smallest Euclidean distance using optimized divide-and-conquer.
-  **Matrix Display**: Output the current state of the quantum board.

---

##  Input Commands

The system accepts the following commands from standard input:

### Board Commands:
- `CREATE_2D size`  
  Followed by `size` lines each with `size` integers (quantum states).

- `SORT_2D ascending`  
  Sorts each row in ascending order.

- `SORT_2D descending`  
  Sorts each row in descending order.

- `INVERSION_2D`  
  Outputs the total number of inversions across the matrix.

- `DISPLAY_2D`  
  Displays the current board row-by-row.

### Player Proximity:
- `CLOSEST_2D num_points`  
  Followed by `num_points` lines, each with 2 integers denoting (x, y) coordinates of players.

### Termination:
- `END`  
  Ends the input.

---

##  Output Format

- `DISPLAY_2D`: Each row of the matrix on a new line with values separated by spaces.
- `INVERSION_2D`: A single integer – the inversion count.
- `CLOSEST_2D`: Four integers: `x1 y1 x2 y2`, where `(x1, y1)` and `(x2, y2)` are coordinates of the closest pair, maintaining input order in case of ties.

---

##  Constraints

- `1 ≤ size ≤ 1000`
- `-10^18 ≤ quantum_state ≤ 10^18 - 1`
- `-10^9 ≤ coordinate ≤ 10^9`
- Total `CLOSEST_2D` points ≤ 10^5
- Max 50 total commands per test case
- Max 3 calls to `DISPLAY_2D`

### Tie-breakers for Closest Pair:
1. Lower squared distance
2. Lower x of first point
3. Lower y of first point
4. Lower x of second point
5. Lower y of second point
6. Original input order (index-based)

---

## 🛠 Tech Stack

- Language: C++
- STL & Custom Utilities: Merge Sort, Functors, Geometry algorithms


