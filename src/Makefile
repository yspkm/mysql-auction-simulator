CC = g++

# mariadb
CCFLAGS  = -Wall -g -lm -I /usr/include/mariadb -lmariadbclient

# mysql 
#CCFLAGS = -Wall -g -lm -I/usr/include/mysql -lmysqlclient 

HDIR = ../include
TDIR = ../
TARGET = ${TDIR}/myauction
OBJECT = main.o Menu.o User.o Query.o Regex.o Item.o
HEADERS = ${HDIR}/dbms.hpp ${HDIR}/Menu.hpp ${HDIR}/User.hpp ${HDIR}/Query.hpp ${HDIR}/Item.hpp ${HDIR}/Regex.hpp ${HDIR}/Item.hpp ${HDIR}/param.hpp

${TARGET}: ${OBJECT}
# mysql 
#	${CC} ${CCFLAGS} -o ${TARGET} ${OBJECT} `mysql_config --cflags --libs`
# mariadb 
	${CC} ${CCFLAGS} -o ${TARGET} ${OBJECT} ${CCLIBS} `mariadb_config --cflags --libs`

main.o: main.cpp ${HEADERS}
	${CC} ${CCFLAGS} -c main.cpp

Menu.o: Menu.cpp ${HEADERS} Item.o
	${CC} ${CCFLAGS} -c Menu.cpp

Query.o: Query.cpp ${HDIR}/User.hpp ${HEADERS}
	${CC} ${CCFLAGS} -c Query.cpp

User.o: User.cpp ${HEADERS}
	${CC} ${CCFLAGS} -c User.cpp

Item.o: Item.cpp ${HEADERS}
	${CC} ${CCFLAGS} -c Item.cpp

Regex.o: Regex.cpp ${HEADERS}
	${CC} ${CCFLAGS} -c Regex.cpp

clean:
	rm -f *.o ${TARGET} *a.out
