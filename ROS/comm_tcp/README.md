comm_tcp: Package in ROS for TCP/IP communication
=================================================

A ROS Catkin package with client and server nodes to communicate with other frameworks on different operating systems using TCP/IP.

Before running the package, make sure the ROS master is up and running:
```
$ roscore
```

Once the master is up, run the following commands:

**For Server Node:**
(Replace 'port_number' by the specific port)
```
$ rosrun comm_tcp server_node <port_number>
```


**For Client Node:**
(Replace 'server_address' and 'port_number' by the correct values)
```
$ rosrun comm_tcp client_node <server_address> <port_number>
```
