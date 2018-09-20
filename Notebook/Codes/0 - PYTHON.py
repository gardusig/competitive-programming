import sys
import bisect

lst = sys.stdin.readlines()
	
n = int(lst[0])
a = [list(map(int, lst[i + 1].split())) for i in range(n)]

sh = []
for i in range(n):
	sh.append(a[i][0])
	sh.append(a[i][1] + 1)
sh.sort()

cnt = [0 for i in range(2 * n)]
for i in range(n):
	lpos = bisect.bisect_left(sh, a[i][0])
	rpos = bisect.bisect_left(sh, a[i][1] + 1)
	cnt[lpos] += 1
	cnt[rpos] -= 1
for i in range(1, 2 * n):
	cnt[i] += cnt[i - 1]
	
ans = [0 for i in range(n + 1)]
for i in range(1, 2 * n):
	ans[cnt[i - 1]] += sh[i] - sh[i - 1]
	
sys.stdout.write(' '.join(str(x) for x in ans[1:n + 1]))