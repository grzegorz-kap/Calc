function [A] = fun(A)
 [m,n]=size(A);
 i=1;

 while i<=m
     j=2;
     while j<=n
     if A(i,j-1)>A(i,j)
        temp = A(i,j);
        A(i,j) = A(i,j-1);
        A(i,j-1)= temp;
        if j>2
          j=j-1;
        end
     else
        j=j+1;
     end
  end
  i=i+1;
 end


 
end