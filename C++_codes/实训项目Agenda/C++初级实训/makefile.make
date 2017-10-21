CC := g++
FLAGS := -std=c++11 -w
Agenda: User.o Date.o Meeting.o Storage.o AgendaService.o AgendaUI.o
	$(CC) $(FLAGS)  User.o Date.o Meeting.o Storage.o AgendaService.o AgendaUI.o -o

User.o: User.cpp
	$(CC) $(FALGS) -c User.cpp

Date.o: Date.cpp
	$(CC) $(FALGS) -c Date.cpp

Meeting.o Date.o: Date.cpp Meeting.cpp
	$(CC) $(FALGS) -c Date.cpp Meeting.cpp

Storage.o: Storage.h Storage.cpp
	$(CC) $(FALGS) -c Storage.cpp

AgendaService.o Storage.o: Storage.h Storage.cpp AgendaService.cpp
	$(CC) $(FALGS) -c Storage.cpp AgendaService.cpp

AgendaUI.o: AgendaService.cpp AgendaUI.cpp
	 $(CC) $(FALGS) -c AgendaService.cpp AgendaUI.cpp