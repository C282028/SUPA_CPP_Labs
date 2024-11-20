CC=g++										#Compiler
FLAGS=-std=c++20 -w 						#Compiler flags
TARGET=AnalyseData							#Executable name
OBJECTS=AnalyseData.o CustomFunctions.o		#Intermediate object files

${TARGET}:${OBJECTS} 						#Make TARGET from OBJECTS
		@echo "Linking..."		
		${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}
		@make clean

AnalyseData.o 		: AnalyseData.cxx
	${CC} ${FLAGS} -c AnalyseData.cxx

CustomFunctions.o	 : CustomFunctions.cxx
	${CC} ${FLAGS} 	-c  CustomFunctions.cxx

clean: #no target just run shell command yo rm object files and emacs backups
		@rm -f *.o *~

cleantarget: #Delete the exectuable
		@rm -f ${TARGET}