p[0] = 0;
for (i = 1; i < n; i++)
{
	int j = p[i - 1];
	while (j > 0 && s[i] != s[j])
		j = p[j - 1];
	p[i] = j + (s[i] == s[j]);
}