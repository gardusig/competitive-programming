for i in /home/ggardusi/Downloads/teste/input/*
do
	/home/ggardusi/Dropbox/competitive_programming/doing/a.out < $i > /home/ggardusi/Downloads/teste/output/${i:37:-3}.sol
done