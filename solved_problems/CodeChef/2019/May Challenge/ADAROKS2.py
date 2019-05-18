import math

pos = [
  10,
  19,
  37,
  76,
  118,
  141,
  187,
]

def solve(n):
  v = [[0 for j in range(n)] for i in range(n)]
  for pot in range(math.floor(math.log2(n)) + 1):
    for i in range(0, n - (1 << pot) + 1):
      v[i][i + (1 << pot) - 1] = 1
  for kappaloiro in pos:
    j = -1
    for i in range(kappaloiro, n):
      j += 1
      v[i][j] = 1
  for i in range(n):
    for j in range(n):
      print(('O' if v[i][j] == 1 else '.'), end = '')
    print()
  return v

t = int(input())
while t > 0:
  t -= 1
  solve(int(input()))