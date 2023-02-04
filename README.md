1.각 파일별 설명

README.md: 현재 이 파일을 의미합니다.
clean.sh: 전체적으로 \*.o 파일과 myauction 실행파일을 정리해줍니다.
compile.sh: 컴파일 및 링킹을 위한 간단한 쉘스크립트입니다.

include

Item.hpp: Item 클래스의 인스턴스에 현재 아이템 정보가 담겨있습니다.
Menu.hpp: 로그인 메뉴를 제외한 모든 Menu 인터페이스와 상태값이 담긴 클래스입니다.
Query.hpp: 모든 sql 쿼리 처리를 담당하는 클래스입니다.
Regex.hpp: 혹시 모르는 입력 에러 등을 방지하기 위해 첨가한 정규식 API 모음입니다.
User.hpp: User 클래스의 인스턴스에 현재 유저의 정보가 로그아웃까지 유지됩니다.
dbms.hpp: 제 리눅스 노트북 db가 mysql이 아닌 mariadb이다 보니 부득이하게 넣었습니다 .
param.hpp: 모든 파라미터 값이 담긴 헤더파일입니다.
run.sh: 실행을 위한 파일로서, db 접근을 위한 정보가 담겨있습니다.

sql

data.sql: 모든 insert문이 있습니다. 월단위로 업데이트는 관리자 창에서 진행됩니다.
ddl.sql: 모든 table과 procedure, function 등이 담겨있습니다.
ddl_mariadb.sql: 제 노트북의 db가 mariadb이므로 사소한 차이를 담았습니다.

src

Item.cpp: Item.hpp의 구현입니다.
Makefile: 프로젝트 빌드를 위한 Makefile입니다.
Menu.cpp: Menu.hpp의 구현입니다.
Query.cpp: Query.hpp의 구현입니다.
Regex.cpp: Regex.hpp의 구현입니다.
User.cpp: User.hpp의 구현입니다.
main.cpp: main함수가 담겨있습니다.

2.사용법

2.1 빌드

    sh compile.sh

2.2 정리

    sh clean.sh

2.3 실행

    sh run.sh

2.4 데이터삽입

    mysql> source ddl.sql
    mysql> source data.sql
