function [a] = fun(z)
	f1=1;
	f2=1;
	f3=1;
	i=0;
	while i<z-2
		f3=f1+f2;
		f1=f2;
		f2=f3;
		i=i+1;
	end
	a=f3;
end