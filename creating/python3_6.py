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

def convert(v):
    ans = []
    for i in range(len(v)):
        ans.append((v[i], i))
    return ans

def main():
    n, m = list(map(int, input().split(' ')))
    a = convert(list(map(int, input().split(' '))))
    b = convert(list(map(int, input().split(' '))))
    a.sort()
    b.sort()
    for i in range(m):
        print(str(a[0][1]) + ' ' + str(b[i][1]))
    for i in range(1, n):
        print(str(a[i][1]) + ' ' + str(b[m - 1][1]))

main()