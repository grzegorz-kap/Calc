tab = [1 4 3  32 3 2 ; 43 32 1 3 4 4 ; 12 4 3 4 2 3]

[m,n] = size(tab)
 
i=1;
j=1;

while i<=m
	 j=2;
	 while j<=n
  		if tab(i,j) > tab(i,j-1)
  			 temp = tab(i,j);
  			 tab(i,j) = tab(i,j-1);
  			 tab(i,j-1) = temp;
 			if j>2
				j=j-1;
			end
		 else
		 	j=j+1;
		 end
	 end
	 i=i+1; 
end

tab