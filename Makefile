TASK = func2for func2forS
#CXX += -Wall -std=c++17
CXX += -Wall -std=c++11 -O3
#CXX += -Wall -O3 

all: $(TASK)

%:      %.cc
	$(CXX) $< -o $@

clean:
	rm -f $(TASK) *.o 


