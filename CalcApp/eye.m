function [A] = eye(M,N)
	A = [];
	i = M;
	while i > 0
	 j = N;
	 while j > 0
		if i==j
			A(i,j)=1;
		else
			A(i,j)=0;
		end
		j=j-1;
	 end
	 i=i-1;
	end

end