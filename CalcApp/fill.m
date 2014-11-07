function [A] = fill (M,N,val)
	A = [];
	i = M;
	while i>=1
		j = N;
		while j>=1
			A(i,j) = val;
			j=j-1;
		end
		i=i-1;
	end
end