#program paths
CC = gcc

#flags
CFLAGS = 

#defult rule
all: bin\\out.exe

#RUN=====================================================================================================
run: bin\\out.exe
	$(info ======================================================================================================running)
	bin\out.exe

#BUILD===================================================================================================

#lists of source and object files
SRC_FILES := $(shell powershell Get-ChildItem src -Recurse -Name -Filter *.c)
OBJ_FILES := $(patsubst %.c, bin\\%.o, $(SRC_FILES))

#link all .o files together
bin\\out.exe: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

#compile .c file to .o file
bin\\%.o: src\\%.c
	powershell $$null = mkdir -Force $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

#CLEAN===================================================================================================

#delete everything in bin folder
clean:
	del $(OBJ_FILES)
	del bin\*.exe