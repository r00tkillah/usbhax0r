dmesg -c

echo "*** inserting and removing hidhunt ***"
rmmod hidhunt
insmod hidhunt.ko
dmesg

