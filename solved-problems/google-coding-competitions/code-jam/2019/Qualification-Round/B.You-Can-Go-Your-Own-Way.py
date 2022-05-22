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
    _ = int(input())
    s = input()
    ans = ''
    for i in s:
      ans += 'E' if i == 'S' else 'S'
    print('Case #' + str(test) + ': ' + ans)
  return 0

main()