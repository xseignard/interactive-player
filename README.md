## Install openframeworks

In the pi home : `cd ~`

[http://openframeworks.cc/setup/raspberrypi/](http://openframeworks.cc/setup/raspberrypi/)

## Install ofxOMXPlayer

```
cd ~/of_v0.9.8_linuxarmv6l_release/addons/
git clone https://github.com/jvcleave/ofxOMXPlayer.git
```

## Install wiringPi

```
cd ~
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
```

## Clone the project

```
cd ~
git clone https://github.com/xseignard/interactive-player.git
```

## Overclock RPi

Set 256mb to the GPU memory via sudo raspi-config

## Compile and run it

You may need to increase swapfile: `sudo nano /etc/dphys-swapfile`

And replace:

```
CONF_SWAPFILE=100
```

by

```
CONF_SWAPFILE=1024
```

Add the env variables to the `/etc/environment` file (once)

```
MAKEFLAGS=-j4
```

Compile and run (for developement)

```
make && make runRelease
```

## More sound

Add the following to `/etc/rc.local`:

```
amixer set PCM,0 100%
```

## `init.d` script

Copy the following

```
sudo cp misc/interactive-player /etc/init.d/
sudo chmod +x /etc/init.d/interactive-player
sudo update-rc.d interactive-player defaults
```

This will make the app run at startup
