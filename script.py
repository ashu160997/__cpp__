import subprocess
import multiprocessing 


def fn1():
    subprocess.run(['./server'])


def fn2():
    subprocess.run(['./client'])



if __name__=="__main__":

    p1=multiprocessing.Process(target=fn1)
    p2=multiprocessing.Process(target=fn2)
    p1.start()
    p2.start()
    p1.join()
    p2.join()
