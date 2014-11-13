function [sorted] = fun(A)
 sorted=A; 
 A(10,10) = 3;
 [m,n]=size(sorted);
 i=1;

 while i<=m
     j=2;
     while j<=n
     if sorted(i,j-1)>sorted(i,j)
        temp = sorted(i,j);
        sorted(i,j) = sorted(i,j-1);
        sorted(i,j-1)= temp;
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