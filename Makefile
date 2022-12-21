NAME		:= libftstl.a

CXX		:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -Iinclude -MMD -MP -O2

CXXFILES	:= src/red_black_tree.cpp
HEADER_DEPS	:= $(CXXFILES:.cpp=.d)
OBJFILES	:= $(CXXFILES:.cpp=.o)

.PRECIOUS: $(OBJFILES)

.PHONY: all
all: $(NAME)

$(NAME): $(NAME)($(OBJFILES))

$(NAME)(%.o): %.o
	ar rcs $(NAME) $<

%.o: %.c Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(HEADER_DEPS) $(OBJFILES)

.PHONY: fclean
fclean:
	${MAKE} clean
	rm -f $(NAME)

.PHONY: re
re:
	${MAKE} fclean
	${MAKE}

.PHONY: run
run:
	${MAKE} -k -C test/
