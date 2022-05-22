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
    s = input()
    a = ''
    b = ''
    for i in s:
      a += '3' if i == '4' else i
      b += '1' if i == '4' else '0'
    print('Case #' + str(test) + ': ' + a + ' ' + b)
  return 0

main()