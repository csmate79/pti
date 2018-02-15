//tutor: Fekete Attila
from time import sleep
import os

width, height = 32, 24 #the resolution of the box
x, y = 10, 10 #current coordinates of the ball
x1, y1 = x, y

while True:
    sleep(0.08)
    os.system("clear");

    x += pow(-1, (x1-1)/(width-3))
    y += pow(-1, (y1-1)/(height-3))
    x1 = x1+1
    y1 = y1+1

    for i in range(0,width):    
        print("#"),
    print("")
    
    for i in range(0,y-1):  
        print("#"),
        for j in range(0,width-2):
            print(" "),
        print("#")

    print(" "),
    for i in range(0,x-1):
        print(" "),
    print("@"),
    for i in range(x+1,width-1):   
        print(" "),
    print("#") 


    for i in range(y,height-2):
        print("#"),
        for j in range(0,width-2):
            print(" "),
        print("#")

    for i in range(0,x):
        print("#"),
    print(" "),
    for i in range(x+1,width):
        print("#"),

    print"\nCoordinates\nx:" , x , "y:" , y
