function [a] = fibb(b)
	if b==0
		a = 0;
	end
	
	if b==1
		a=1;
	end
	
	if b>1
		a = fibb(b-1)+fibb(b-2);
	end
end