# ~ <template>

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

# ~ </template>

class Solution:
  
  def __init__(self):
    pass
    
  def main(self):
    pass
  
def main():
  Solution().main()

main()