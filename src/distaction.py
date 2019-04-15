from dronekit import connect, VehicleMode, LocationGlobal, LocationGlobalRelative
import math
from pymavlink import mavutil
import time
from turtle import Turtle, Screen
import array as arr
import os
import sys
import pygame

#import winsound

vehicle = connect('127.0.0.1:14551', wait_ready=True)
watchdist = input("Set the WATCH distance: ")
alertdist = input("Set the ALERT distance: ")
flag = 0
indexflag = 0
status_flag_enable = True
statusflag = False

#sensorbuffer = arr.array('I', [sys.maxint,sys.maxint,sys.maxint,sys.maxint,sys.maxint,sys.maxint,sys.maxint,sys.maxint])

sensorbuffer = []
for i in range(8):
    sensorbuffer.append(sys.maxint)

position0, position1, posiiton2, posiiton3, position4, position5, position6, position7 = 0, 0, 0, 0, 0, 0, 0, 0
previousmode = ''

def beep():
    print ("\a")

def checkmode():
    global statusflag
    statusflag = False
    for i in range(8):
        if sensorbuffer[i] <= alertdist:
            statusflag = True

# initialize all the axis and screen
def axis(turtle, distance, tick):
    position = turtle.position()
    turtle.pendown()
    for _ in range(0, distance, tick):
        turtle.forward(tick)
    turtle.setposition(position)
    for _ in range(0, distance, tick):
        turtle.backward(tick)


def my_method(self, name, msg):
    #x = math.cos(math.radians(22.5))*msg.current_distance
    #alert = alertdist

    print(msg.current_distance)
    global sensorbuffer
    sensorbuffer[msg.orientation]= msg.current_distance
    #print(x)
    global flag
    global indexflag 
    global turtle
    global screen
    global status_flag_enable
    global statusflag 
   
    if flag ==0:
        #x axis
        screen = Screen()
        turtle = Turtle(visible=False)
        screen.bgcolor("black")
        turtle.pencolor("green")
        turtle.speed(0)
        turtle.penup()
        axis(turtle, watchdist, 30)
        #45 degree
        turtle.penup()
        turtle.home()
        turtle.setheading(45)
        axis(turtle, watchdist, 30)
        #y axis
        turtle.penup()
        turtle.home()
        turtle.setheading(90)
        axis(turtle, watchdist, 30)
        #135 degree
        turtle.penup()
        turtle.home()
        turtle.setheading(135)
        axis(turtle, watchdist, 30)
        # watch circle
        turtle.penup()
        turtle.home()
        turtle.goto(0, -watchdist)
        turtle.pendown()
        turtle.circle(watchdist)
        #alert circle
        turtle.penup()
        turtle.home()
        turtle.goto(0, -alertdist)
        turtle.pendown()
        turtle.circle(alertdist)
        flag = 1

        
    #update dots in graph
    #global position0, position1, posiiton2, posiiton3, position4, position5, position6, position7
    global position0
    
    
    checkmode()
    #statusflag = True

    #print (statusflag)
    #print ("///////")
    #print (status_flag_enable)
    if statusflag == True and status_flag_enable == True:
        #print( "trigger HHHHHH")
        vehicle.mode = VehicleMode("BRAKE")
        status_flag_enable = False
        if vehicle.groundspeed<=0.25*1:
            vehicle.mode = VehicleMode("ALT_HOLD")
            status_flag_enable = False
            print("-----------")
            print("now it's BACK in Althold mode")
            print("-----------")


    if sensorbuffer[msg.orientation] <= watchdist:
        if sensorbuffer[msg.orientation] <= alertdist:
            beep()

        print("It's sensor:",repr(msg.orientation))
        turtle.penup()
        if msg.orientation == 0:
            #position0 = turtle.posiion()
            if indexflag == 0:
                indexflag =1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(0, msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==1:
            #position1 = turtle.position()
            if indexflag == 0:
                indexflag =1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(math.cos(math.radians(45))*msg.current_distance,math.sin(math.radians(45))*msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==2:
            #position2 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(msg.current_distance,0)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==3:
            #position3 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(math.cos(math.radians(45))*msg.current_distance,-math.sin(math.radians(45))*msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==4:
            #position4 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(0, -msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==5:
            #position5 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(-math.cos(math.radians(45))*msg.current_distance, -math.sin(math.radians(45))*msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==6: 
            #position6 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")  
            turtle.goto(-msg.current_distance,0)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()

        elif msg.orientation ==7:
            #position7 = turtle.position()
            if indexflag == 0:
                indexflag = 1
            else:
                turtle.goto(position0)
                turtle.dot(10, "black")
            turtle.goto(-math.cos(math.radians(45))*msg.current_distance,math.sin(math.radians(45))*msg.current_distance)
            position0 = turtle.position()
            turtle.dot(10,"red")
            turtle.penup()    

vehicle.add_message_listener('DISTANCE_SENSOR',my_method)

    
while True:
    i=0        
                          
