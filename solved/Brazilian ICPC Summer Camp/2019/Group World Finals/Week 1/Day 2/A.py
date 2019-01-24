import atexit
import io
import sys

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
  sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())
  
def solve(n, m, h, w, dp):
  if (n, m) in dp:
    return dp[(n, m)]
  if (n <= h and m <= w) or (m <= h and n <= w):
    dp[(n, m)] = 0
    return dp[(n, m)]
  ans = 1123456789
  if n > 1:
    ans = min(ans, solve((n + 1) >> 1, m, h, w, dp))
  if m > 1:
    ans = min(ans, solve(n, (m + 1) >> 1, h, w, dp))
  dp[(n, m)] = ans + 1
  return dp[(n, m)]

def main():
  dp = {}
  n, m, h, w = list(map(int, input().split(' ')))
  print(solve(n, m, h, w, dp))
  return 0

main()
