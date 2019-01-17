import atexit
import io
import math
import sys

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
    sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())

def main():
	h, w, x, y = list(map(int, input().split(' ')))
	gcd = math.gcd(x, y)
	x //= gcd
	y //= gcd
	ans = min(h // x, w // y)
	print(str(x * ans) + ' ' + str(y * ans))

main()