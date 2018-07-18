all : pcap_test

pcap_test: main.o printarr.o
	g++ -g -o pcap_parser main.o printarr.o -lpcap

printarr.o:
	g++ -g -c -o printarr.o printarr.cpp

main.o:
	g++ -g -c -o main.o main.cpp

clean:
	rm -f pcap_parser
	rm -f *.o

