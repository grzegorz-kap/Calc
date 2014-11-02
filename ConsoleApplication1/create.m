function [A] = create(m,n)
	i = 1;
	iter = 1;
	A=[];
	while i<=m
		j = 1;
		column = [];
		while j<=n
			column = [column;iter];
			iter = iter+1;
			j=j+1;
		end
		A=[A column];
		i=i+1;
	end
end