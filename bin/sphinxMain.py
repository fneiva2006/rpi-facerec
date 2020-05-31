######         RESET AUDIO CARD BEFORE RUNNING         ##############
import os, sys, time, webbrowser
from demo import *
from multiprocessing import Process

directory = "/home/pi/pocketsphinx-0.8/src/programs \n"
tf=open('stt.txt','w')
tf.write("begin")
tf.close()
dic = "3145"

def listen():
    bscript = "./contRec2.sh "+dic
    os.system(bscript)
try:
    p1 = Process(target=listen)
    p2 = Process(target=loop)
    p1.start()
    p2.start()
    time.sleep(3)
    os.system("./TTS.sh 'Ready'")
    print("READY")
    p2.join()
    p1.terminate()
    os.system("pkill pocketsphinx_co")
    sys.exit(1)
except (SystemExit, KeyboardInterrupt):
    os.system("pkill pocketsphinx_co")
    sys.exit(1)
