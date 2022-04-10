# The Mountain: Solution

A hill climbing algorithm written completely in C.

## 📑 Description

Your program wakes up at the bottom of a mountain. The whole area is shrouded in deep fog so you only have visibility at a short distance around. Your goal is to get to the top of the mountain in as little time as possible.

The landscape is implemented as a 2D matrix on top of which a mountain of a given height and with some irregularities (plateaus) has been placed. The mountain has a single peak.

Each element of the 2D matrix contains a value that represents the altitude (height) of that cell, with the mountain peak representing the highest point in the landscape, or the maximum matrix value.

You will not have access to the 2D matrix, or the matrix’s dimensions (height and width). The only thing you can do is make calls to the function

```c
void generate_view(float view[VIEW_SIZE][view_size], int center_y, int center_x)
```

that will populate a 2D view array from the landscape matrix centered on the `center_y` and `center_x` coordinates (the row and column respectfully). Every time you call this function the program will increment your call count with the goal being to implement a search solution that makes the least calls to generate_view.

When you believe that you have found the peak at a position `x`, `y` you must call the function `int declare_peak(x,y)`. The function will return `1` (true) if the peak is correctly identified or `0` (false) otherwise. You can call this function any number of times, however every time it is called it will increment your call count and this will add up to your total.

**NOTE**: The `generate_view` function will stop working after it’s been called as many times as the number of cells in the landscape matrix. Same for `declare_peak` which will only return `0` after that point.

## ⛰️ Approach

Generate a view matrix at a random position in the landscape using the `generate_view` function.

## ⚒️ Get Started

1. Compile the gradient file into an executable.

```shell
$ gcc gradient.c gradient_sol.c -lm -o gradient
```

2. Run the gradient executable file.

```shell
$ ./gradient
```

Optionally, direct the output of the program into an output text file.

```shell
$ ./gradient > data/output.txt
```

P. Richárd Szilágyi, 2022
