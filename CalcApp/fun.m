function [a,b] = fun(z)
	if z==0
	 a = 0;
	else
		if z==1
			a=1;
		else
			a=fun(z-1)+fun(z-2);
		end
	end
end

[fun(11) 3- 9 89;-8 9- 7 8;+1 +2 3 4;[1 2+ 3 4]];