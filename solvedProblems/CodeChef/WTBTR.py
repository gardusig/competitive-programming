import atexit
import io
import sys
from collections import defaultdict

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
  sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())

def solve(v):
  v.sort()
  current = v[1] - v[0]
  for i in range(2, len(v)):
    current = min(current, v[i] - v[i - 1])
  return current

def main():
  t = int(input())
  while t > 0:
    t -= 1
    n = int(input())
    a = defaultdict(int)
    b = defaultdict(int)
    for i in range(n):
      x, y = list(map(int, input().split()))
      a[x + y] += 1
      b[x - y] += 1
    valid = False
    for i in a:
      if a[i] > 1:
        valid = True
    for i in b:
      if b[i] > 1:
        valid = True
    a = list(a.keys())
    b = list(b.keys())
    ans = 0 if valid == True else min(solve(a), solve(b))
    print(str(ans // 2) + '.' + ('5' if ans & 1 else '0'))
  return 0

main()