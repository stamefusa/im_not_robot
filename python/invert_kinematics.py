from math import pi, acos, sin, cos, atan2

def main():
    args = input("入力： ").split()
    if len(args) != 2:
        print("引数は2つ必要です")
        return
    
    L1 = 100
    L2 = 100
    
    x = float(args[0])
    y = float(args[1])
    print("x: " + str(x) + ", y: " + str(y))

    theta2 = pi - acos((x*x + y*y - L1*L1 - L2*L2) / (2*L1*L2))
    theta1 = atan2(y, x) - atan2((L2*sin(theta2)), (L1 + L2*cos(theta2)))
    print("theta1: " + str(theta1) + ", theta2: " + str(theta2))

    rad1 = theta1 * 180 / pi
    rad2 = theta2 * 180 / pi
    print("theta1: " + str(rad1) + ", theta2: " + str(rad2))

if __name__ == '__main__':
    main()  