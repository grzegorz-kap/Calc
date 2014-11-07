function [A] = eye(M,N)
	A = [];
	i = M;
	one = [1];
	zero = [0];
	while i > 0
	 j = N;
	 while j > 0
		if i==j
			A(i,j)=one;
		else
			A(i,j)=zero;
		end
		j=j-1;
	 end
	 i=i-1;
	end

end

