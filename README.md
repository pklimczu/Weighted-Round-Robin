# Weighted-Round-Robin

This is an application written in **C++ and Qt5** (including **QML**). The purpose of that application is both to provide a simple tool for event simulation of **Weighted Round Robin algorithm** (it can be used at - for instance - universities as a demo) as well as kind of practice C++ and Qt skills. Below you can find a short guid about using this simulator.

# Short guide - how to use it?
## Starting screen
![Main View](https://i.imgur.com/gRPFFJa.png)

**Basic parameters**
This two parameters are common for the whole simulation. **Throughput** determines how many kilobits per second can be trasmitted. **Duration** is the time that we want to simulate - it is not a real time.

**Queues**
Here we can determine parameters of every single query. 
* **Lambda** provides a parameter for Poisson distribution and can be considered as "how many packets per second (on average) should be generated" - so if we put 100, we will have aproximately 100 packets per second generated. 
* **Avg size** is average packet size in bits. Due to the fact that this is simulation, average packet size is the only size that packets of that queue can have. 
* **Weight** describes importance of the queue. More important queue has higher priority and in the case of congestion, loses here will be smaller (or there will be no loses). 
* **Buffor size** is the number of packets that can await for their turn in case of arrival when another packet is sending. On the one hand, big buffor size can reduce number of rejected packets but on the other it increases latencies in real world (however, latencies are not taken into consideration here).

If we have our parameters ready, we can add a queue by clicking "Add" button. Newly added queue will appear in the list below **Queue's list** header.
When all queues are added, the simulation can start by clicking "Start" button. In the case of entering incorrect argument, appropriate message will be displayed. Otherwise simulation will be started and additional overscreen will appear in order to provide information about current progress, as on the picture below:
![Incorrect argument](https://i.imgur.com/rjKwaoX.png)

![Waiting screen](https://i.imgur.com/RywlAwZ.png)

## Results screen
![Results screen](https://i.imgur.com/ChZzONC.png)

In the case that simulation succesfully ended (and there is no known reason for another possibility), results can be inspected in the **Results view**. It is also possible to save results in text form - clicking on button "Save results" will save the results to the folder with simulation.

## How does it work screen
![How does it work?](https://i.imgur.com/TR6nhiT.png)

Last view contains an excerpt from Wikipedia about Weighted Round Robin in its own.
