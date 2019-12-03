# Assignment A1 Program

## How to run the program

To run the program you simply need to compile the java program and provide the path to the text file you will be providing as input to the program. See example below.

```sh
javac Graph.java && java Graph "input.txt"
```

Few comments about the program:

- For both BFS and each occurence of DFS the algorithms have the potential to search up to M states. M being the max number of states specified by the input file. On average I found the runtime to be `O(N * M)` where N is the number of states provided by the input file.
- I utilized the explored map for both BFS and DFS in order to cut down on unnecessary searching, the key-value pair is `<diff, State>` where diff is the diff of the domino in the given state.

### - Domenico Maisano
