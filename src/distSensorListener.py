from dronekit import connect 

vehicle = connect('127.0.0.1:14550', wait_ready=True)
file = open('msgprintout.txt','w')

def my_method(self, name, msg):
    # msgStr = str(msg)
    # file.write(msgStr)
    # file.write('\n')
    print(msg.current_distance)


vehicle.add_message_listener('DISTANCE_SENSOR',my_method)
while True:
    i=0
