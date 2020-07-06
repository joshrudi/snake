snake: 
	g++ -std=c++11 -pthread main.cpp View.cpp Snake.cpp InputManager.cpp PelletManager.cpp -o snake

clean:
	rm -rf snake