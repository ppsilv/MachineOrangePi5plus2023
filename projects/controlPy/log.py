#!/usr/bin/python
import logging
from logging.handlers import SysLogHandler
import thread
import time


# Define a function for the thread
def print_time( ):
   while True:
      time.sleep(20)
      print( time.ctime(time.time()) )

def verificaMaquinas():
    while True:
        time.sleep(10)
        print("Verifica maquinas running...")

def createThreads():
    # Create two threads as follows
    try:
        thread.start_new_thread( print_time, ("Thread-1", 2, ) )
        thread.start_new_thread( verificaMaquinas, ("Thread-2", 4, ) )
    except:
        print ("Error: unable to start thread")


def main():
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.DEBUG)
    handler = SysLogHandler(
        facility=SysLogHandler.LOG_DAEMON,
        address='/dev/log'
        )

    formatter = logging.Formatter(
        fmt="%(asctime)s - %(filename)s:%(funcName)s:%(lineno)d %(levelname)s - '%(message)s'",
        datefmt="%Y-%m-%d %H:%M:%S"
        )
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    logger.debug('Creating threads...!')
    createThread()
    while True:
        time.sleep(100);
        print("Main thread...")


if __name__ == '__main__':
    main()



