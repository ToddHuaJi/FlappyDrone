from scapy.all import *

srcIP ='192.168.43.93'
dstIP = '192.168.43.250'
srcPort = 14550
dstPort = 35215

#RAW(abc)
#print payload
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
p = IP(dst=dstIP)/UDP(sport=RandShort(),dport=dstPort)/Raw("Hallo world!")
s.connect((dstIP,dstPort))
s.send(bytes(p))
print "[+] Request Sent!"
#send(IP(dst = dstIP)/ICMP())
