//枚举子集
for (int j = 0; j < n; j++)
for (int i = 0; i < (1 << n); i++)
    if ((i >> j) & 1)
        f[i] += f[i ^ (1 << j)];
//枚举超集
for (int j = 0; j < n; j++)
for (int i = (1 << n) - 1; ~i; i--) 
	if(!((i >> j) & 1)) 
		f[i] += f[i ^ (1 << j)];
