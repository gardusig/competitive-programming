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
  t = int(input())
  for test in range(1, t + 1):
    n, p = list(map(int, input().split(' ')))
    v = list(map(int, input().split(' ')))
    v.sort()
    sum = [0 for i in range(n + 1)]
    for i in range(1, n + 1):
      sum[i] = sum[i - 1] + v[i - 1]
    ans = 1123456789123456
    for i in range(p, n + 1):
      ans = min(ans, (v[i - 1] * p) - (sum[i] - sum[i - p]))
    print('Case #' + str(test) + ': ' + str(ans))
  return 0

main()