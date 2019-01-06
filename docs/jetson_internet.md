# Jetson internet access

Often, we need to provide internet access to the Jetson to install and update software or configuration files. 
It becomes frustrating when the device is glued or otherwise attached to the robot, and/or when the only internet access available is through Wi-Fi on a laptop (or even a mobile access point, spaghetti monster forbid).

The best solution is to use the laptop SSH'd into the Jetson as a proxy server. 
SSHuttle will need to be installed on the Jetson, and the laptop will need internet access for this to work.

## On the laptop:
```
# Start the SSH Daemon
sudo systemctl start sshd

# Note the laptop's ethernet IP address. When connected to the robot, it should be something like [laptop ip]
ifconfig
```

## On the Jetson:
```
# Use SSHuttle to connect to the laptop and begin forwarding packets.
# Note that you can also pass '-f' if you want this to run in the background.
sshuttle --dns -r user@[laptop ip] -x[laptop ip] 0/0
```

## Installing SSHuttle
If SSHuttle has not been installed yet, you will need to find some other (temporary) means of providing the Jetson with internet access. You may want to try an ethernet bridge from your laptop to the jetson.
Installing SSHuttle is as easy as:
```
sudo apt install sshuttle
```

## Dealing with FMS BS
If the router has been configured for FMS (I.E. you are at a competition), you may have to use approved ports. You will need to set your SSH server and sshuttle to use an approved range. 
Refer to https://wpilib.screenstepslive.com/s/currentCS/m/troubleshooting/l/705152-fms-whitepaper to determine which ports are allowed.

You should configure your laptop's SSH server to use an approved port:
```
# /etc/ssh/sshd_config
...
Port [ssh port]
...
```
And ask SSHuttle to connect on that port
```
sshuttle --dns -r user@[laptop ip]:[ssh port] -x[laptop ip] 0/0
```
