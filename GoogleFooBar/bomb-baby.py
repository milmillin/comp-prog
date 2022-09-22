def solve(x, y):
    if x > y:
        return solve(y, x)
    if x == 1:
        return y - 1
    if x == 0:
        return -4874651321
    return y / x + solve(y % x, x)

def solution(x, y):
    x = int(x)
    y = int(y)
    res = solve(x, y)
    if res >= 0:
        return str(res)
    return "impossible"


