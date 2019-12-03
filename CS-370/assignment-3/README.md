# Assignment A3 Program

## How to run the program

To run the program you will need to use python3, I am specifically using python3 v3.7.4, however you should be fine with any version of 3.7 or higher just to be safe.

Below is an example command you can type in the terminal to run the code _(python/python3 depending on your PATH settings)_

```sh
python3 classifier.py "inputFile.txt" 0.1 0.01 0.2 100 -v
```

The program takes the following positional arguments:

- fileName
- stepSize
- epsilon
- M
- numRestarts

lastly, it also takes an optional verbose flag, -v or --verbose

you can also view the available CLI args options by running

```sh
python3 classifier.py --help
```

#### - Domenico Maisano
