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


def solve_test_case():
    pass


def main():
    for test in range(1, int(input()) + 1):
        print('Case #' + str(test) + ': ')
        solve_test_case()


main()
