#Windows Makefile
all: main.o Uteis.o QuickSort.o OdBlocosSubstituicao.o OdBlocos2F.o
	@gcc ./obj/main.o ./obj/Uteis.o ./obj/QuickSort.o ./obj/OdBlocosSubstituicao.o ./obj/OdBlocos2F.o -o ordenacoa.exe -Wall

debug: 
	@gcc ./src/*.c -o pesquisaDebug.exe -g

main.o: ./src/main.c
	@gcc -c ./src/main.c -o ./obj/main.o

Uteis.o: ./src/Uteis.c
	@gcc -c ./src/Uteis.c -o ./obj/Uteis.o

QuickSort.o: ./src/QuickSort.c
	@gcc -c ./src/QuickSort.c -o ./obj/QuickSort.o

OdBlocosSubstituicao.o: ./src/OdBlocosSubstituicao.c
	@gcc -c ./src/OdBlocosSubstituicao.c -o ./obj/OdBlocosSubstituicao.o

OdBlocos2F.o: ./src/OdBlocos2F.c
	@gcc -c ./src/OdBlocos2F.c -o ./obj/OdBlocos2F.o

run:
	@./ordenacoa.exe

go:
	@make all
	@make run

clean:
	@del *.exe /q
	@cd data && del *.dat /q && \
	@cd ./src/obj && del *.o /q && \
	@cls