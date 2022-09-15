# Problem 2: Game of Life (on C++)

---------------------------------------------------

## Steps to run on Linux terminal or any UNIX terminal : <br/>
a.  clone the project from github <br/>
b.  In project folder open a terminal and run ``` g++ code.cc -o out.exe ```<br/>
c.  To run the code write command ``` ./out.exe ``` <br/>

---------------------------------------------------
## Test Cases
### Case 1: 
``` Input A:
(Block pattern - Still life)
1, 1
1, 2
2, 1
2, 2
Output A:
1, 1
1, 2
2, 1
2, 2 
```
---------------------------------------------------
### Case 2:
```
Input B
(Boat pattern - Still life)
0, 1
1, 0
2, 1
0, 2
1, 2
Output B
0, 1
1, 0
2, 1
0, 2
1, 2
```
---------------------------------------------------
### Case 3:
```
Input C
(Blinker pattern - oscillator)
1, 1
1, 0
1, 2
Output C
1, 1
0, 1
2, 1
```
---------------------------------------------------
### Case 4:
```
Input D
(Toad pattern - two phase oscillator)
1, 1
1, 2
1, 3
2, 2
2, 3
2, 4
Output D
0, 2
1, 1
1, 4
2, 1
2, 4
3, 3
```
---------------------------------------------------
