CXX		:= g++
WARNINGS	:= -Wall -Wextra
CXXFLAGS	:= -std=c++98 $(WARNINGS) -MMD -MP -Ofast -g0 -I. -I../include

CXXFILES	:= $(shell find . -type f -name '*.cpp')
HEADER_DEPS	:= $(CXXFILES:.cpp=.d)
BENCHMARKS	:= $(CXXFILES:.cpp=.out)
FTBENCHMARKS	:= $(addsuffix .ft, $(BENCHMARKS))
STDBENCHMARKS	:= $(addsuffix .std, $(BENCHMARKS))

ifdef verbose
	.SILENT	:=
else
	.SILENT := @
endif

.PHONY: all
all: run

.PHONY: run
run: $(BENCHMARKS)

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
			printf "\x1B[1;32m%.2fx times faster\x1B[0m\n"		\
				$$IMPROVEMENT;					\
		else								\
			printf "\x1B[1;31m%.2fx slower\x1B[0m\n" 		\
				$$(echo 1.0 / $$IMPROVEMENT | bc -l);		\
	fi;									\

-include $(HEADER_DEPS)
.PRECIOUS: $(STDBENCHMARKS)
%.out.std: %.cpp Makefile
	$(.SILENT)$(CXX) $(CXXFLAGS) -DBENCHMARK_STD -o $@ $<

-include $(HEADER_DEPS)
.PRECIOUS: $(FTBENCHMARKS)
%.out.ft: %.cpp Makefile
	$(.SILENT)$(CXX) $(CXXFLAGS) -DBENCHMARK_FT -o $@ $<

.PHONY: clean
clean:
	rm -f $(HEADER_DEPS) $(FTBENCHMARKS) $(STDBENCHMARKS)
