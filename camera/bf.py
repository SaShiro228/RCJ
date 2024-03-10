from math import sin,cos,fabs,sqrt,asin


# x1=int(input("X1"))
# y1=int(input("Z1"))
# a1=float(input("angle1"))

# x2=int(input("X2"))
# y2=int(input("Z2"))
# a2=float(input("angle2"))
x2=7
y2=4
a2=180+163
x1=15
y1=12
a1=180+144

a1=3.14/180*a1  
a2=3.14/180*a2

g90=1.5708
g180=3.14159
g270=4.71239
g360=6.28319
def count():
    l1=fabs(x1-x2)
    l2=fabs(y1-y2)
    l3=sqrt((l1**2)+(l2**2))

    if a2>=g90 and a2<=g180 and a1<=a2:
        x=l3*sin(a1+asin(l2/l3))*sin(a2-g90)/sin(a2-a1)
        y=l3*sin(a1+asin(l2/l3))*sin(g180-a2)/sin(a2-a1)
        x=x2+x
        y=y2+y
    elif a2<=g90 and a1<a2:
        x=l3*sin(a1+asin(l2/l3))*sin(g90-a2)/sin(a2-a1)
        y=l3*sin(a1+asin(l2/l3))*sin(a2)/sin(a2-a1)
        x=x2-x
        y=y2+y
    elif a2<=g270 and a2>=g180 and a1>=a2:
        x=l3*sin(g360-asin(l2/l3)-a1)*sin(g270-a2)/sin(a1-a2)
        y=l3*sin(g360-asin(l2/l3)-a1)*sin(a2-g180)/sin(a1-a2)
        x=x2+x
        y=y2-y
    elif a2>=g270 and a1>=a2:
        x=l3*sin(g360-asin(l2/l3)-a1)*sin(a2-g270)/sin(a1-a2)
        y=l3*sin(g360-asin(l2/l3)-a1)*sin(g360-a2)/sin(a1-a2)
        x=x2-x
        y=y2-y
    elif a2<=g180 and a2>=g90 and a1>=a2:
        x=l3*sin(g360-asin(l2/l3)-a1)*sin(a2-g90)/sin(a1-a2)
        y=l3*sin(g360-asin(l2/l3)-a1)*sin(g180-a2)/sin(a1-a2)
        x=x2+x
        y=y2+y
    elif a2<=g90 and a1>=a2:
        x=l3*sin(a1-asin(l1/l3)-g270)*sin(g90-a2)/sin(g90+g360-a1-a2-asin(l2/l3)+asin(l1/l3))
        y=l3*sin(a1-asin(l1/l3)-g270)*sin(a2)/sin(g90+g360-a1-a2-asin(l2/l3)+asin(l1/l3))
        x=x2+x
        y=y2-y
    elif a2>=g270 and a1<=a2:
        x=l3*sin(a1-asin(l1/l3)-g270)*sin(a2-g270)/sin(a2-a1)
        y=l3*sin(a1-asin(l1/l3)-g270)*sin(g360-a2)/sin(a2-a1)
        x=x2-x
        y=y2-y
        print(0)

    # x=round(x)
    # y=round(y)
    print(x, y)

count()

input()