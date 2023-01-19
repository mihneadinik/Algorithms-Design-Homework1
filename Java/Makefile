#Dinica Mihnea-Gabriel 323CA

TARGETS=prinel statistics walsh crypto
build:	$(TARGETS)

walsh: walsh.cpp
	g++ walsh.cpp -o walsh

statistics: Statistics.java
	javac $^

prinel: prinel.cpp
	g++ prinel.cpp -o prinel

crypto: crypto.cpp
	g++ crypto.cpp -o crypto

run-p1:
	./walsh

run-p2:
	java Statistics

run-p3:
	./prinel

run-p4:
	./crypto

clean:
	rm -f *.class $(TARGETS) *.o
