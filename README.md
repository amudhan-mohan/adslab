# Advanced Data Structures and Algorithms (ADS) Lab

C programs for the 12 ADS lab experiments, each with its program (`.c`) and a sample run (`.txt`).
All programs compile with `gcc -Wall -Wextra` without warnings, and every sample output was produced by running the program.

## Experiments

| No. | Program | Experiment | Files |
|-----|---------|------------|-------|
| 1 | Quick Sort | Sort a list of integers in ascending order | `ex001.c`, `ex001.txt` |
| 2 | Merge Sort | Sort a list of names (strings) in descending order | `ex002.c`, `ex002.txt` |
| 3 | Hashing | Dictionary with insert, search, delete and display using division and multiplication hashing (linear probing) | `ex003.c`, `ex003.txt` |
| 4 | Heap | Max heap with insert, extract max, display and heap sort | `ex004.c`, `ex004.txt` |
| 5 | Fibonacci Heap | Insert, get min, extract min (with consolidation), display | `ex005.c`, `ex005.txt` |
| 6 | AVL Tree | Self-balancing tree with all four rotations; inorder and preorder traversal | `ex006.c`, `ex006.txt` |
| 7 | BFS | Breadth first search using an adjacency matrix (handles disconnected graphs) | `ex007.c`, `ex007.txt` |
| 8 | DFS | Depth first search using an adjacency matrix | `ex008.c`, `ex008.txt` |
| 9 | Dijkstra | Shortest distances and paths from a vertex in a weighted graph | `ex009.c`, `ex009.txt` |
| 10 | Kruskal | Minimum cost spanning tree with total cost and connectivity check | `ex010.c`, `ex010.txt` |
| 11 | B+ Tree | Insertion with leaf and internal node splits, level-order display and linked leaves | `ex011.c`, `ex011.txt` |
| 12 | Bloom Filter | Membership test with three hash functions | `ex012.c`, `ex012.txt` |

Each `.txt` file shows the program run with the input typed after each prompt. Experiments with more than one case (for example duplicates, a disconnected graph, or an absent element) have each run in the same file.

## Requirements

- A C compiler such as GCC (Linux, macOS, or MinGW on Windows), or **Dev-C++** on Windows (see below)
- A C99 or newer language standard (the programs declare variables inside `for` loops, such as `for (int i = 0; ...)`)

## Compile and run

One program:

```bash
gcc ex001.c -o ex001
./ex001
```

On Windows, run `ex001.exe` instead of `./ex001`.

All programs:

```bash
for f in ex*.c; do gcc -Wall -Wextra "$f" -o "${f%.c}"; done
```

Compile Experiment 2 with plain `gcc` or `-std=gnu99` (not strict `-std=c99`), because it uses `strdup`, which is a POSIX function.

## Run on Windows using Dev-C++

1. Install [Dev-C++](https://www.embarcadero.com/free-tools/dev-cpp) (Embarcadero Dev-C++ 6.x, or Orwell Dev-C++ 5.11).
2. Open a program with **File → Open** (for example `ex001.c`). Keep the `.c` extension so Dev-C++ compiles it as C and not C++.
3. Set the language standard (do this once):
   - Go to **Tools → Compiler Options**.
   - Open the **Settings** tab, then **Code Generation**.
   - Set **Language standard (-std)** to **GNU C99** (or **GNU C11**).
   - Click **OK**.
4. Choose **Execute → Compile & Run** (or press **F11**).
5. A console window opens. Type the inputs shown in the matching `.txt` file (for example `ex001.txt`).
   For the menu programs (Experiments 3, 4 and 5) type the option number each time, and choose the Exit option to finish.

**Common problems**

| Problem | Fix |
|---------|-----|
| `error: 'for' loop initial declarations are only allowed in C99 mode` | Do step 3 and set the standard to GNU C99 or GNU C11. Older Dev-C++ versions (5.11) default to an older standard. |
| Warning about `strdup` in Experiment 2 | Use **GNU C99**, not plain **ISO C99**. `strdup` is not part of strict ISO C. |
| The file compiles as C++ and shows odd errors | Save or rename the file with the `.c` extension. |
| Compiler Options changes do not apply | Click **OK**, then recompile with **Execute → Rebuild All** (F12). |

## Example (Experiment 1)

```
Enter number of elements: 5
Enter 5 integers: 8 5 1 3 6
Sorted array in ascending order:
1 3 5 6 8
```

## Notes

- Experiments 3, 4, 5 and 12 are menu or prompt driven, so type the inputs shown in the matching `.txt` file to get the same output.
- Experiment 3 uses deleted-slot markers so a key can be deleted and inserted again without creating a duplicate.
- Experiment 12 uses a 29-bit array and three hash functions, so searching for a word that was never added can still say "may be present" (a false positive). Searching for `grape` after adding `apple`, `mango`, `orange` and `banana` says "definitely not present".
