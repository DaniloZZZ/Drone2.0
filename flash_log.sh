#make flash

rm ~/capture.log
echo "Now listening to /dev/ttyUSB0"
touch ~/capture.log
(stty 38400 cs8 -ixon; cat) < /dev/ttyUSB0 > ~/capture.log &
echo "Waiting for board to start..."
LCNT=100
ln=`wc -l < ~/capture.log`
echo "$ln Lines read"
while [ $ln -lt $LCNT ]
do
	ln=$(wc -l < ~/capture.log)
	echo "$ln Lines read"
	sleep 1s
done
kst2 ~/capture.log -f -1 -n 505 -P P1 -y 2 -y 3 -y 4 -P P2 -y 1 -s1

