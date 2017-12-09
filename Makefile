
POC	=	poc

SRCS	=	bind.c main.c
OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra

RM	=	rm -f

all:		$(POC)

$(POC):		$(OBJS)
		$(CC) -o $(POC) $(OBJS)

clean:
		$(RM) $(OBJS) $(POC)
