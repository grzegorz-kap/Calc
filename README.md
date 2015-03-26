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
## Command entering
Instructions can be separated by semicolon, comma or new line:
```
 a=3+2i , b=2; d= 2 + ... continuing instruction in new line
 3*10;
```
To prevent command result display use semicolon.

## IF instruction

```
 if (a==1)
    c=2
 elseif (3)
    d=2
 else
    2
 end
```
## Loops
```
A=[]; 
for i=1:0.1:10
  A(1,i)=i*i;
end

while i<10
  i=i-1;
end
```

Inside loops 'break' and 'continue' keywords might be used.

## Functions
Function must be declered in seperate ".m" file. The file name must be the same as a function name. File has to start with function declaration (see fallowing example).
```
 function [out1,out2] = methodName(in1,in2,in3) 
    out1=in1*in2;
    out2=in1+in3;
 end
```
To exit function or script use 'return' keyword.

## Comments
```
% Single line comment

%{ Multiline
    comment %}
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
```
rand(m)
rand(m,n)
eye(m,n)
ones(m,n)
zeros(m,n)
```

# Matrix indexing
```
 A(i,j)
 A(i) (matrix A treated as column vector)
 A(k:m,j)
 A(:,j)
 A(i,:)
 A(end,i)
 A(end+3,j)=10; (automatic matrx expansion)
 ```

To remove matrix entire rows or columns use fallowing command:
```
A(:,2:3) = [] %removing 2nd and 3rd column from A
```

# Arithmetic operators
```
 A+B
 A.+B
 +A
 A-B
 A.-B
 -A
 A*B
 A.*B
 A/B (compute A*inv(B))
 A./B
 A\B (solves A*x=B)
 A.\B
 A^B
 A.^B
 A'
 A.'
```
# Relational operatos
```
 A==B
 A~=B
 A<B
 A<=B
 A>B
 A>=B
```
# Logical operators
```
 expression1 | expression2
 expression1 & expression2
 expression1 || expression2 %(short-circuit OR operator, applied only to scalar arguments)
 expression2 && expression2 %(short-circuit AND operator)
 ~negation
```
# Build in functions
 ```
 a=sqrt(A)
 a=log(b) or a=log(b,c)
 a=log2(c)
 a=log10(d)
 sin(A)
 cos(A)
 tan(A)
 cot(A)
 conj(3+2i) == 3-2i 
 det(A)
 inv(A) == A^-1
 x=url(A,b)
 [L,U,P]=lu(A)
```
# Matrix sizes
```
 [m,n]=size(A)
 a=length(C)
 numel(A)
 iscolumn(A)
 isrow(A)
 isempty(A)
 isscalar(A)
 isvector(A)
 rows(A)
 cols(A)
```
# Data plots
KLab can draw 2D and 3D plots using fallowing methods:
```
 plot(x,y)
 plot3(x,y,z)
 mesh(x,y,z)
```
## Example plot
```
eps=2.2204e-16;
temp = -8:0.5:8;
[m,n]=size(temp);
x=[];
y=[];
for i=1:n
	x(i,:) = temp;
	y(i,:) = temp;
end
y=y';
R = (x.^2 + y.^2).^0.5 + eps;
Z = sin(R)./R;
mesh(x,y,Z);
```

# Workspace variables removing
```
clear % remove all variables
clear var1, var2, var3
clear ('var1','var2',...,'varN')
```
# Save variables to file
```
save file_name % save all variables
save file_name var1 var2 ... varN
```
# Load variables from file
```
load file_name % load all variables from file
load file_name var1 var2 ... varN
```
# Error generating
```
% plik def_fun.m
function d = det_fun(A)
    if rows(A)~=cols(A)
        error('A must be squere matrix!');
    end
    d=det(A);
end
```
```
% command line
>> det_fun(rand(3,7))
det_fun Col: 3, Line: 3 A must be squere matrix!
```
