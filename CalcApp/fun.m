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
	b=1
end