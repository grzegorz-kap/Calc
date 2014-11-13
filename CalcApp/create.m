function [A] = create(m,n)
	val = 1;
	A = [];
	for j = 1:n
		for i = 1:m
			A(i,j) = val;
			val = val + 30;
		end
	end
end