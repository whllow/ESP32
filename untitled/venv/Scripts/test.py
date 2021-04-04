from pyb import LED

LED4 = LED(4)

while True:
    LED4.toggle()
    print('Hello')
    print('-------')
    pyb.delay(1000)