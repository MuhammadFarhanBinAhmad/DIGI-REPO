PRG=x.out

GCC=g++

GCCFLAGS=-std=c++17 -pedantic-errors -Wall -Wextra -O3

VALGRIND_OPTIONS=-q --leak-check=full --track-origins=yes
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines

OBJECTS0= test.cpp
DRIVER0= 

# Change input file names here as necessary.
QUESTION_1A_STUDENT_PREF= studentprefs.txt
QUESTION_1A_HOSPITAL_PREF= hospitalprefs.txt
QUESTION_1B_STAFF_PREF= staffpref.txt 

OUTPUT_TXT_FILE= out
TXT= .txt

gcc0:
	$(GCC) -o $(PRG) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) 
0 1:
	./$(PRG) $(QUESTION_1A_STUDENT_PREF) $(QUESTION_1A_HOSPITAL_PREF) $(QUESTION_1B_STAFF_PREF) $@ > $(OUTPUT_TXT_FILE)$@$(TXT)
mem0:
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(QUESTION_1A_STUDENT_PREF) $(QUESTION_1A_HOSPITAL_PREF) $(QUESTION_1B_STAFF_PREF) 0 > $(OUTPUT_TXT_FILE)0$(TXT)
mem1:
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(QUESTION_1A_STUDENT_PREF) $(QUESTION_1A_HOSPITAL_PREF) $(QUESTION_1B_STAFF_PREF) 1 > $(OUTPUT_TXT_FILE)1$(TXT)
clean:
	rm -f *.exe *.o 
run:
	./$(PRG) $(QUESTION_1A_STUDENT_PREF) $(QUESTION_1A_HOSPITAL_PREF) $(QUESTION_1B_STAFF_PREF) 1 > $(OUTPUT_TXT_FILE)$(TXT)
