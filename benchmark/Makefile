CXX		:= g++
WARNINGS	:= -Wall -Wextra
CXXFLAGS	:= -std=c++98 $(WARNINGS) -Ofast -g0 -I. -I../include \
			-I../test/support -L.. -lftstl

CXXFILES	:= $(shell find . -type f -name '*.cpp')
BENCHMARKS	:= $(CXXFILES:.cpp=.out)
FTBENCHMARKS	:= $(addsuffix .ft, $(BENCHMARKS))
STDBENCHMARKS	:= $(addsuffix .std, $(BENCHMARKS))
HEADER_DEPS	:= $(addsuffix .d, $(BENCHMARKS))

ifdef verbose
	.SILENT	:=
else
	.SILENT := @
endif

.PHONY: all
all: run

.PHONY: run
run: $(BENCHMARKS)

-include $(HEADER_DEPS)
%.out: %.out.ft %.out.std
	@printf "%-30s" "$(notdir $(basename $@)):";				\
	FT_RESULT=$$(./$<);							\
	STD_RESULT=$$(./$(word 2,$^));						\
	IMPROVEMENT=$$(echo "$$STD_RESULT / $$FT_RESULT" |			\
		sed -E 's/([+-]?[0-9.]+)[eE]\+?(-?)([0-9]+)/(\1*10^\2\3)/g'|	\
		bc -l);								\
	BETTER=$$(echo "$$IMPROVEMENT > 1.0" | bc);				\
	if [ "$$BETTER" -eq "1" ];						\
		then								\
			printf "\x1B[1;32m%.2fx faster\x1B[0m\n"		\
				$$IMPROVEMENT;					\
		else								\
			printf "\x1B[1;31m%.2fx slower\x1B[0m\n" 		\
				$$(echo 1.0 / $$IMPROVEMENT | bc -l);		\
	fi;									\

.PRECIOUS: $(STDBENCHMARKS)
%.out.std: %.cpp Makefile
	$(.SILENT)$(CXX) -DBENCHMARK_STD -o $@ $< $(CXXFLAGS)

.PRECIOUS: $(FTBENCHMARKS)
-include $(HEADER_DEPS)
%.out.ft: %.cpp Makefile
	$(.SILENT)$(CXX) -MMD -MP -DBENCHMARK_FT -o $@ $< $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(HEADER_DEPS) $(FTBENCHMARKS) $(STDBENCHMARKS)
