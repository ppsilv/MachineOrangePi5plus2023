import subprocess
import os
import time 
from datetime import datetime

dataPadrao = "%Y%m%d"
dataNow = datetime.now().strftime(dataPadrao)
dataOld = dataNow 
filename = "maquinas_" + dataOld + ".txt" 
filename1 = "internet_" + dataOld + ".txt" 
fout = open(filename,"a")
fout1 = open(filename1,"a")
datePattern = "%Y%m%d %H%M%S"
totalPing1 = 0

def ping(ip):
  global fout, dataNow, dataOld  
  with open(os.devnull, "wb") as limbo:
    ret=subprocess.Popen(["ping", "-c", "1", "-n", "-W", "1", ip],stdout=limbo, stderr=limbo).wait()
    current_dateTime = datetime.now().strftime(datePattern)
    dataNow = datetime.now().strftime(dataPadrao)
    if dataNow != dataOld:
      fout.write( current_dateTime + ": rotating log\n")
      fout.close()
      fout1.write( current_dateTime + ": rotating log\n")
      fout1.close()
      dataOld = dataNow
      filename = "maquinas_" + dataOld + ".txt" 
      filename1 = "internet_" + dataOld + ".txt" 
      fout = open(filename,"a")
      fout1 = open(filename1,"a")

    if ret:
      print( ip, "INATIVO")
      fout.write( current_dateTime + ": " + ip + " inativo\n")
    else:
      print( ip, "ATIVO")
      fout.write( current_dateTime + ": " + ip + " ativo\n")
    fout.flush()

def ping1(ip):
    global totalPing1
    current_dateTime = datetime.now().strftime(datePattern)
    ret1 = ping(ip)
    if ret1:
        fout1.write( current_dateTime + ": " + ip + " inativo\n")
        totalPing1 += 1
        if totalPing1 == 5:
            fout1.write( current_dateTime + ": total de vezes que o " + ip + " retornou inativo é" + totalPing1 + "\n")
        ping2(ip)    
    else:
        totalPing1 = 0
        fout1.write( current_dateTime + ": " + ip + " ativo\n")
    fout1.flush()

def ping2(ip):
    global totalPing1
    print("ping2: pinging... ",ip)
    response = os.popen(f"ping -c 1 {ip} ").read()
    fout1.write( current_dateTime + response + "\n" )
    if("name resolution") in response:
        totalPing1 += 1
        fout1.write( current_dateTime + " ping2: " + ip + " local dns error\n")
    else:
        totalPing1 = 0
        fout1.write( current_dateTime + " ping2: " + ip + " ativo\n")

    fout1.flush()



while True:
  with open("ip_list.txt") as file:
    park = file.read()
    park = park.splitlines()
  for ip in park:
    ret = ping(ip)

  ping1("yahoo.com")
  time.sleep(10)

fout.close()





#with open(os.devnull, "wb") as limbo:
#        for n in range(1, 100):
#                ip="192.168.15.{0}".format(n)
#                result=subprocess.Popen(["ping", "-c", "1", "-n", "-W", "1", ip],
#                        stdout=limbo, stderr=limbo).wait()
#                if result:
#                        print( ip, "inactive")
#                else:
#                        print( ip, "active")

