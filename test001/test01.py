# 在这里写上你的代码 :-)
from machine import Pin #导入 Pin 模块
led=Pin(2,Pin.OUT) #构建 led 对象，GPIO2,输出
led.value(1) #点亮 LED，也可以使用 led.on()
