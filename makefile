CC=g++
CFlags=-std=c++11 -lcurl
SRC=src/main.cpp src/weather/weather.cpp src/calendar/calendar.cpp
EXE=magic_mirror
PKGFlags=`pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

all: $(SRC) $(EXE)

$(EXE):  $(SRC)
	$(CC) $(PKGFlags) $(CFlags) $(SRC) -o $(EXE)
clean:
	rm -f $(EXE)