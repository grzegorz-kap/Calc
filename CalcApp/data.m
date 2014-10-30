i = 1;
z = 1;
while i~=3
	i = i+1;
	z=-z;
	if z>= 0
		i=i
	end
end

a=[ [1;3;4] [5;3;4] [5;4;2] ]

L1=lu(a)
[L2,U2]=lu(a)
[L3,U3,P3]=lu(a)
detA = det(a)
invA = inv(a)