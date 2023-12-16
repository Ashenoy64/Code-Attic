import time
import threading


capacity = 5

buffer = [-1]*capacity

in_index = 0
out_index = 0

mut = threading.Semaphore()
empty = threading.Semaphore(capacity)
full = threading.Semaphore(0)


class Producer(threading.Thread):
    def run(self):
        global capacity, buffer, in_index, out_index
        global mut, empty ,full

        item_produced = 0

        counter = 0
        while item_produced < 5:
            empty.acquire()
            mut.acquire()
            counter+=1
            buffer[in_index]=counter
            in_index = (in_index+1)%capacity
            print("Producer produced an item")
            mut.release()
            full.release()
            time.sleep(1)

            item_produced+=1


class Consumer(threading.Thread):
    def run(self):
        global capacity, buffer, in_index, out_index
        global mut, empty ,full

        item_consumed = 0

        counter = 0
        while item_consumed < 5:
            full.acquire()
            mut.acquire()
            
            item = buffer[out_index]
            out_index = (out_index+1)%capacity
            print("Consumer consumed an item",item)
            mut.release()
            empty.release()
            time.sleep(2.5)

            item_consumed+=1

prod = Producer()
cons= Consumer()

prod.start()
cons.start()

prod.join()
cons.join()