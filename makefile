#Windows Makefile
all: main.o uteis.o intercalacao2F.o selecSub.o sortInterno.o quickSortExterno.o heap.o
	@gcc ./obj/main.o ./obj/uteis.o ./obj/intercalacao2F.o ./obj/selecSub.o ./obj/sortInterno.o ./obj/quickSortExterno.o ./obj/heap.o -o ordenacao.exe -Wall

debug: 
	@g++ ./src/*.c -o ordenacaoDebug.exe -g

runDebug:
	@gdb ./ordenacaoDebug.exe

main.o: ./src/main.c
	@gcc -c ./src/main.c -o ./obj/main.o -Wall

uteis.o: ./src/uteis.c
	@gcc -c ./src/uteis.c -o ./obj/uteis.o -Wall

intercalacao2F.o: ./src/intercalacao2F.c
	@gcc -c ./src/intercalacao2F.c -o ./obj/intercalacao2F.o -Wall

selecSub.o: ./src/selecSub.c
	@gcc -c ./src/selecSub.c -o ./obj/selecSub.o -Wall

quickSortExterno.o: ./src/quickSortExterno.c
	@gcc -c ./src/quickSortExterno.c -o ./obj/quickSortExterno.o -Wall

sortInterno.o: ./src/sortInterno.c
	@gcc -c ./src/sortInterno.c -o ./obj/sortInterno.o -Wall

heap.o: ./src/heap.c
	@gcc -c ./src/heap.c -o ./obj/heap.o -Wall

run:
	@./ordenacao.exe

out:
	@./ordenacao.exe > data/testes/output.out

in:
	@./ordenacao.exe < data/testes/input.in

go:
	@make all
	@make run

clean:
	@del *.exe /q
	@cd data && del *.dat /q && \
	@cd ./src/obj && del *.o /q && \
	@cls