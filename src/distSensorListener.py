from dronekit import connect, VehicleMode, LocationGlobal, LocationGlobalRelative
import math
from pymavlink import mavutil
import time
from turtle import Turtle, Screen
import array as arr

vehicle = connect('127.0.0.1:14550', wait_ready=True)
watchdist = input("Set the WATCH distance: ")
alertdist = input("Set the ALERT distance: ")
index = 0
flag =0
indexflag = 0
#arr.array('i', [0,0,0,0,0,0,0,0])
position0, position1, posiiton2, posiiton3, position4, position5, position6, position7 = 0, 0, 0, 0, 0, 0, 0, 0


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
    #print(x)
    global flag
    global indexflag
    global turtle
    global screen
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
    global index
    if index > 7:
        index = 0

    #global position0, position1, posiiton2, posiiton3, position4, position5, position6, position7
    global position0
    if msg.current_distance > alertdist and msg.current_distance <= watchdist:
        print("It's sensor: ", repr(index))
        turtle.penup()
        if index ==0:
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

        elif index ==1:
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

        elif index ==2:
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

        elif index ==3:
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

        elif index ==4:
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

        elif index ==5:
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

        elif index ==6: 
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

        elif index ==7:
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

        print("-----------")
        vehicle.mode = VehicleMode("BRAKE")
        print("it's within the alert distance, control override!")
        print("now it's in BRAKE mode")
        print("-----------")
    else:
        print("-----------")
        vehicle.mode = VehicleMode("GUIDED")
        print("now it's BACK in GUIDED mode")
        print("-----------")

    index+=1


def arm_and_takeoff(aTargetAltitude):
    """
    Arms vehicle and fly to aTargetAltitude.
    """

    print("Basic pre-arm checks")
    # Don't let the user try to arm until autopilot is ready
    while not vehicle.is_armable:
        print(" Waiting for vehicle to initialise...")
        time.sleep(1)

        
    print("Arming motors")
    # Copter should arm in GUIDED mode
    vehicle.mode = VehicleMode("GUIDED")
    vehicle.armed = True

    while not vehicle.armed:      
        print(" Waiting for arming...")
        time.sleep(1)

    print("Taking off!")
    vehicle.simple_takeoff(aTargetAltitude) # Take off to target altitude

    # Wait until the vehicle reaches a safe height before processing the goto (otherwise the command 
    #  after Vehicle.simple_takeoff will execute immediately).
    while True:
        print(" Altitude: ", vehicle.location.global_relative_frame.alt)      
        if vehicle.location.global_relative_frame.alt>=aTargetAltitude*0.95: #Trigger just below target alt.
            print("Reached target altitude")
            break
        time.sleep(1)


#Arm and take of to altitude of 5 meters
arm_and_takeoff(5)



"""
Convenience functions for sending immediate/guided mode commands to control the Copter.

The set of commands demonstrated here include:
* MAV_CMD_CONDITION_YAW - set direction of the front of the Copter (latitude, longitude)
* MAV_CMD_DO_SET_ROI - set direction where the camera gimbal is aimed (latitude, longitude, altitude)
* MAV_CMD_DO_CHANGE_SPEED - set target speed in metres/second.


The full set of available commands are listed here:
http://dev.ardupilot.com/wiki/copter-commands-in-guided-mode/
"""

def condition_yaw(heading, relative=False):
    """
    Send MAV_CMD_CONDITION_YAW message to point vehicle at a specified heading (in degrees).

    This method sets an absolute heading by default, but you can set the `relative` parameter
    to `True` to set yaw relative to the current yaw heading.

    By default the yaw of the vehicle will follow the direction of travel. After setting 
    the yaw using this function there is no way to return to the default yaw "follow direction 
    of travel" behaviour (https://github.com/diydrones/ardupilot/issues/2427)

    For more information see: 
    http://copter.ardupilot.com/wiki/common-mavlink-mission-command-messages-mav_cmd/#mav_cmd_condition_yaw
    """
    if relative:
        is_relative = 1 #yaw relative to direction of travel
    else:
        is_relative = 0 #yaw is an absolute angle
    # create the CONDITION_YAW command using command_long_encode()
    msg = vehicle.message_factory.command_long_encode(
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_CMD_CONDITION_YAW, #command
        0, #confirmation
        heading,    # param 1, yaw in degrees
        0,          # param 2, yaw speed deg/s
        1,          # param 3, direction -1 ccw, 1 cw
        is_relative, # param 4, relative offset 1, absolute angle 0
        0, 0, 0)    # param 5 ~ 7 not used
    # send command to vehicle
    vehicle.send_mavlink(msg)


def set_roi(location):
    """
    Send MAV_CMD_DO_SET_ROI message to point camera gimbal at a 
    specified region of interest (LocationGlobal).
    The vehicle may also turn to face the ROI.

    For more information see: 
    http://copter.ardupilot.com/common-mavlink-mission-command-messages-mav_cmd/#mav_cmd_do_set_roi
    """
    # create the MAV_CMD_DO_SET_ROI command
    msg = vehicle.message_factory.command_long_encode(
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_CMD_DO_SET_ROI, #command
        0, #confirmation
        0, 0, 0, 0, #params 1-4
        location.lat,
        location.lon,
        location.alt
        )
    # send command to vehicle
    vehicle.send_mavlink(msg)



"""
Functions to make it easy to convert between the different frames-of-reference. In particular these
make it easy to navigate in terms of "metres from the current position" when using commands that take 
absolute positions in decimal degrees.

The methods are approximations only, and may be less accurate over longer distances, and when close 
to the Earth's poles.

Specifically, it provides:
* get_location_metres - Get LocationGlobal (decimal degrees) at distance (m) North & East of a given LocationGlobal.
* get_distance_metres - Get the distance between two LocationGlobal objects in metres
* get_bearing - Get the bearing in degrees to a LocationGlobal
"""

def get_location_metres(original_location, dNorth, dEast):
    """
    Returns a LocationGlobal object containing the latitude/longitude `dNorth` and `dEast` metres from the 
    specified `original_location`. The returned LocationGlobal has the same `alt` value
    as `original_location`.

    The function is useful when you want to move the vehicle around specifying locations relative to 
    the current vehicle position.

    The algorithm is relatively accurate over small distances (10m within 1km) except close to the poles.

    For more information see:
    http://gis.stackexchange.com/questions/2951/algorithm-for-offsetting-a-latitude-longitude-by-some-amount-of-meters
    """
    earth_radius = 6378137.0 #Radius of "spherical" earth
    #Coordinate offsets in radians
    dLat = dNorth/earth_radius
    dLon = dEast/(earth_radius*math.cos(math.pi*original_location.lat/180))

    #New position in decimal degrees
    newlat = original_location.lat + (dLat * 180/math.pi)
    newlon = original_location.lon + (dLon * 180/math.pi)
    if type(original_location) is LocationGlobal:
        targetlocation=LocationGlobal(newlat, newlon,original_location.alt)
    elif type(original_location) is LocationGlobalRelative:
        targetlocation=LocationGlobalRelative(newlat, newlon,original_location.alt)
    else:
        raise Exception("Invalid Location object passed")
        
    return targetlocation;


def get_distance_metres(aLocation1, aLocation2):
    """
    Returns the ground distance in metres between two LocationGlobal objects.

    This method is an approximation, and will not be accurate over large distances and close to the 
    earth's poles. It comes from the ArduPilot test code: 
    https://github.com/diydrones/ardupilot/blob/master/Tools/autotest/common.py
    """
    dlat = aLocation2.lat - aLocation1.lat
    dlong = aLocation2.lon - aLocation1.lon
    return math.sqrt((dlat*dlat) + (dlong*dlong)) * 1.113195e5


def get_bearing(aLocation1, aLocation2):
    """
    Returns the bearing between the two LocationGlobal objects passed as parameters.

    This method is an approximation, and may not be accurate over large distances and close to the 
    earth's poles. It comes from the ArduPilot test code: 
    https://github.com/diydrones/ardupilot/blob/master/Tools/autotest/common.py
    """	
    off_x = aLocation2.lon - aLocation1.lon
    off_y = aLocation2.lat - aLocation1.lat
    bearing = 90.00 + math.atan2(-off_y, off_x) * 57.2957795
    if bearing < 0:
        bearing += 360.00
    return bearing



"""
Functions to move the vehicle to a specified position (as opposed to controlling movement by setting velocity components).

The methods include:
* goto_position_target_global_int - Sets position using SET_POSITION_TARGET_GLOBAL_INT command in 
    MAV_FRAME_GLOBAL_RELATIVE_ALT_INT frame
* goto_position_target_local_ned - Sets position using SET_POSITION_TARGET_LOCAL_NED command in 
    MAV_FRAME_BODY_NED frame
* goto - A convenience function that can use Vehicle.simple_goto (default) or 
    goto_position_target_global_int to travel to a specific position in metres 
    North and East from the current location. 
    This method reports distance to the destination.
"""

def goto_position_target_global_int(aLocation):
    """
    Send SET_POSITION_TARGET_GLOBAL_INT command to request the vehicle fly to a specified LocationGlobal.

    For more information see: https://pixhawk.ethz.ch/mavlink/#SET_POSITION_TARGET_GLOBAL_INT

    See the above link for information on the type_mask (0=enable, 1=ignore). 
    At time of writing, acceleration and yaw bits are ignored.
    """
    msg = vehicle.message_factory.set_position_target_global_int_encode(
        0,       # time_boot_ms (not used)
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_FRAME_GLOBAL_RELATIVE_ALT_INT, # frame
        0b0000111111111000, # type_mask (only speeds enabled)
        aLocation.lat*1e7, # lat_int - X Position in WGS84 frame in 1e7 * meters
        aLocation.lon*1e7, # lon_int - Y Position in WGS84 frame in 1e7 * meters
        aLocation.alt, # alt - Altitude in meters in AMSL altitude, not WGS84 if absolute or relative, above terrain if GLOBAL_TERRAIN_ALT_INT
        0, # X velocity in NED frame in m/s
        0, # Y velocity in NED frame in m/s
        0, # Z velocity in NED frame in m/s
        0, 0, 0, # afx, afy, afz acceleration (not supported yet, ignored in GCS_Mavlink)
        0, 0)    # yaw, yaw_rate (not supported yet, ignored in GCS_Mavlink) 
    # send command to vehicle
    vehicle.send_mavlink(msg)



def goto_position_target_local_ned(north, east, down):
    """	
    Send SET_POSITION_TARGET_LOCAL_NED command to request the vehicle fly to a specified 
    location in the North, East, Down frame.

    It is important to remember that in this frame, positive altitudes are entered as negative 
    "Down" values. So if down is "10", this will be 10 metres below the home altitude.

    Starting from AC3.3 the method respects the frame setting. Prior to that the frame was
    ignored. For more information see: 
    http://dev.ardupilot.com/wiki/copter-commands-in-guided-mode/#set_position_target_local_ned

    See the above link for information on the type_mask (0=enable, 1=ignore). 
    At time of writing, acceleration and yaw bits are ignored.

    """
    msg = vehicle.message_factory.set_position_target_local_ned_encode(
        0,       # time_boot_ms (not used)
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_FRAME_LOCAL_NED, # frame
        0b0000111111111000, # type_mask (only positions enabled)
        north, east, down, # x, y, z positions (or North, East, Down in the MAV_FRAME_BODY_NED frame
        0, 0, 0, # x, y, z velocity in m/s  (not used)
        0, 0, 0, # x, y, z acceleration (not supported yet, ignored in GCS_Mavlink)
        0, 0)    # yaw, yaw_rate (not supported yet, ignored in GCS_Mavlink) 
    # send command to vehicle
    vehicle.send_mavlink(msg)



def goto(dNorth, dEast, gotoFunction=vehicle.simple_goto):
    """
    Moves the vehicle to a position dNorth metres North and dEast metres East of the current position.

    The method takes a function pointer argument with a single `dronekit.lib.LocationGlobal` parameter for 
    the target position. This allows it to be called with different position-setting commands. 
    By default it uses the standard method: dronekit.lib.Vehicle.simple_goto().

    The method reports the distance to target every two seconds.
    """
    
    currentLocation = vehicle.location.global_relative_frame
    targetLocation = get_location_metres(currentLocation, dNorth, dEast)
    targetDistance = get_distance_metres(currentLocation, targetLocation)
    
    
    remainingDistance=get_distance_metres(vehicle.location.global_relative_frame, targetLocation)

    while remainingDistance>targetDistance*0.01: #Stop action if we are no longer in guided mode.
        #print "DEBUG: mode: %s" % vehicle.mode.name
        gotoFunction(targetLocation)
        remainingDistance=get_distance_metres(vehicle.location.global_relative_frame, targetLocation)
        print("Distance to target: ", remainingDistance)
        if remainingDistance<=targetDistance*0.05:
            print("Reached target")
            break
        time.sleep(2)

print("TRIANGLE path using standard Vehicle.simple_goto()")

print("Set groundspeed to 20m/s.")
vehicle.groundspeed=20

print("Position North 30 West -20")
goto(30, -20)

vehicle.add_message_listener('DISTANCE_SENSOR',my_method)

print("Position North 80 East 50")
goto(80, 50)

print("Position North -80 West -50")
goto(-80, -50)

while True:
    i=0                                      