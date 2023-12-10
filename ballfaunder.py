from math import sin,cos,fabs,sqrt,raw,asin


x1=int(input("X coordinate of the 1st location (integer):"))
y1=int(input("Z coordinate of the 1st location (integer):"))
a1=float(input("Lateral angle displayed (1 decimal digit):"))

x2=int(input("X coordinate of the 2nd location (integer):"))
y2=int(input("Z coordinate of the 2nd location (integer):"))
a2=float(input("Lateral angle displayed  (1 decimal digit):"))

a1=3.14/180*a1  
a2=3.14/180*a2

# def compute():
#     if a1==a2:  
#         return print("ERROR: The two angles are equal.")    
    
#     x=(cos(a2)*(cos(a1)*y1-sin(a1)*x1)-cos(a1)*(cos(a2)*y2-sin(a2)*x2))/sin(a2-a1)  
#     y=(sin(a2)*(sin(a1)*x1-cos(a1)*y1)-sin(a1)*(sin(a2)*x2-cos(a2)*y2))/sin(a1-a2)  
#     cor = [x, y]
#     return cor

# print(compute())
# input()

# def count():
#     l1=fabs(x1-x2)
#     l2=fabs(y1-y2)
#     l3=sqrt((l1**2)+(l2**2))
#     x=l3*sin(a1+asin(l2/l3))*sin(a2 - 90)

print(a1, a2)

input()