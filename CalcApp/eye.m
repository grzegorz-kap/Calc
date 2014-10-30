function [A] = eye(M,N)
	A=[];
	i = 1;
	while i<=M
		j=1;
		row = [];
		while j<=N
			if i==j
				row = [row 1];
			else
				row = [row 0];
			end
			j=j+1;
		end
		
		A=[A ; row];

		i=i+1;
	end

end