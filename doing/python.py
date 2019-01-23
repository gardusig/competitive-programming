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

def main():
  n = int(input())
  dp = [0 for i in range(n + 5)]
  for i in range(1, n + 5):
    current = ((i + 1) * i) // 2
    while current <= n:
      dp[current] += 1
      current += i
  ans = 0
  for i in range(1, n + 5):
    if n % i == 0:
      ans += dp[i] * dp[n // i]
  print(ans)
  return 0

main()