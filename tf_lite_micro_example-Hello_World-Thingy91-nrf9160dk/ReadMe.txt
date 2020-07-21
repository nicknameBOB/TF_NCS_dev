Tips and trics to build and flash:


Tenerflow hello world example using Zephyr no Thingy52 and Thingy91 products form Nordic Semiconductor
This code exampel uses RTT to comunicate so to se if the program is sucsessfully installed use J-Link RTT Viewr.


Thingy52:
west build -b nrf52_pca20020
# make shure to erase and reset the device first(some truble may ucure if u dont).
nrfjprog -r
nrfjprog -e
west flash

Thingy91:
west build -b thingy91_nrf9160ns
west flash
