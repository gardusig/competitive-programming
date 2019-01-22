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
  
def solve(n):
  i = 1
  while True:
    if (((i + 1) * i) >> 1) > n:
      return i - 1
    i += 1

def main():
  s = input()
  have = 0
  for i in s:
    if i == 'A':
      have += 1
  print(solve(have))

main()
