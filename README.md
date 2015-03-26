# Calc
Calc is small Matlab language interpreter. The applications supports only basic Matlab operations.
I'm currently creating new interpeter from scratch with improved stability and performance.

## To compile requires:
- Boost 1.57
- Qt5
- Visual Studio 2013
- Qt Vs Addin
- DISLIN

# Data types
## Scalar types
double:
``` 
a=2+3i;
```
mpf_float (100 bit)
```
b=mpf_float(543e+45599999)
```

## String
To create a string use two apostrophes:
```
string_variable = 'Hello world'
```

## Matrix
To create a matrix use fallowing instruction:
```
A = [1 3 -3 ; 1+10 3*10 3 ; [3 3 2]]
%or
A = [ 1 3 -3
    1+10 3*10 3
    [3 3 2]]

%mpf_float matrix
B = mpf_float(A);
```
# Syntax

## Language fundamentals
### Command entering
Instructions can be separated by semicolon, comma or new line:
```
 a=3+2i , b=2; d= 2 + ... continuing instruction in new line
 3*10;
```
To prevent command result display use semicolon.

### IF instruction

```
 if (a==1)
    c=2
 elseif (3)
    d=2
 else
    2
 end
```
### Loops
```
A=[]; 
for i=1:0.1:10
  A(1,i)=i*i;
end

while i<10
  i=i-1;
end
```
### Functions
Function must be declered in seperate ".m" file. The file name must be the same as a function name. File has to start with function declaration (see fallowing example).
```
 function [out1,out2] = methodName(in1,in2,in3) 
    out1=in1*in2;
    out2=in1+in3;
 end
```
# Fast vector genarating
```
i = 1:10; % default step is always 1
ii = 1:0.1:10;
```

# Matrix connection
```
>> A = [1 ; 2 ; 3];
>> B = [ A [4 3; 5 4 ; 6 5] ]
B=
1  4   3
2  5   4
3  6   5

>> C = [ A ; [4 3; 5 4 ; 6 5] ]
Col: 28, Line: 1 Dimensions of matrices being concatenated are not consistent.
>> C = [ [ A [10 ; 11 ; 12-3 ] ] ; [4 3; 5 4 ; 6 5] ]
C=
1   10
2   11
3   9
4   3
5   4
6   5
```
# Matrix generating methods
- rand(m)
- rand(m,n)
- eye(m,n)
- ones(m,n)
- zeros(m,n)

# Matrix indexing
- A(i,j)
- A(i) (matrix A treated as column vector)
- A(k:m,j)
- A(:,j)
- A(i,:)
- A(end,i)
- A(end+3,j)=10; (automatic matrx expansion)

To remove matrix entire rows or columns use fallowing command:
```
A(:,2:3) = [] %removing 2nd and 3rd column from A
```

# Data plots
KLab can draw 2D and 3D plots using fallowing methods:
- plot(x,y)
- plot3(x,y,z)
- mesh(x,y,z)
