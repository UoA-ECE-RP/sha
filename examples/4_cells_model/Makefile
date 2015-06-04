# compile every executable
compile: APC NPC1 NPC2 NPC3 gA gB gC loop 
 

APC: cell1D.c APCio.c wait.h wait.c
		gcc cell1D.c APCio.c wait.c wait.h -o APC -lm

NPC1: cell1D.c NPC1io.c wait.h wait.c
		gcc cell1D.c NPC1io.c wait.h wait.c -o NPC1 -lm

NPC2: cell1D.c NPC2io.c wait.h wait.c
		gcc cell1D.c NPC2io.c wait.h wait.c -o NPC2 -lm

NPC3: cell1D.c NPC3io.c wait.h wait.c
		gcc cell1D.c NPC3io.c wait.h wait.c -o NPC3 -lm

gA: g1.c gioA.c wait.h wait.c
		gcc g1.c gioA.c wait.h wait.c -o gA -lm

gB: g1.c gioB.c wait.h wait.c
		gcc g1.c gioB.c wait.h wait.c -o gB -lm

gC: g2.c gioC.c wait.h wait.c
		gcc g2.c gioC.c wait.h wait.c -o gC -lm

loop: loop.c wait.h wait.c
		gcc loop.c wait.h wait.c -o loop -lm

EXE = $(wildcard *.exe)

launch: $(EXE)
		start APC.exe
		start NPC1.exe
		start NPC2.exe
		start NPC3.exe				
		start gA.exe
		start gB.exe
		start gC.exe
		start loop.exe


# clean executable files
clean_exe:
		rm -rf *.exe

clean_files:
		rm -rf file2.csv file5.csv file6.csv file7.csv file8.csv file9.csv result.csv NPCx.csv
		fsutil file createnew file2.csv 0
		fsutil file createnew file5.csv 0
		fsutil file createnew file6.csv 0
		fsutil file createnew file7.csv 0
		fsutil file createnew file8.csv 0
		fsutil file createnew file9.csv 0
		fsutil file createnew result.csv 0
		fsutil file createnew NPCx.csv 0

 
