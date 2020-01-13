SleepTracer: SleepTracerMain.o SleepTracerFunctions.o
	g++ SleepTracerMain.o SleepTracerFunctions.o -o SleepTracer
SleepTracerFunctions.o: SleepTracerFunctions.cpp SleepTracer.h
	g++ -c SleepTracerFunctions.cpp

SleepTracerMain.o: SleepTracerMain.cpp SleepTracer.h
	g++ -c SleepTracerMain.cpp

clean:
	rm *.o SleepTracer
