OBJ = main.c\
      fcfs.c\
      sjf.c\
      priority.c\
      rRobin.c\
      common.c\
      chart.c

start:	$(OBJ) common_function.h common_type.h
	gcc $(OBJ) -o final -g



