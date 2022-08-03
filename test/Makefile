# utility makefile for running tests

# Copyright (C) 2022 Daan Meijer
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
CXX		:= g++
WARNINGS	:= -Wall -Wextra -Werror -Wstrict-aliasing -pedantic \
		   -fmax-errors=5 -Wunreachable-code -Wcast-align -Wcast-qual \
		   -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
		   -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
		   -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
		   -Wshadow -Wsign-promo -Wstrict-null-sentinel \
		   -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused \
		   -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
ANALYZER	:=
CXXFLAGS	:= -std=c++98 $(WARNINGS) $(ANALYZER) -I../include -Isupport -MMD -MP -DFT_TEST

CXXFILES	:= $(shell find . -type f -name '*.cpp')
HEADER_DEPS	:= $(CXXFILES:.cpp=.d)
TSTFILES	:= $(CXXFILES:.cpp=.out)

BIN_DIR		:= bin

.PHONY:	all
all: run

.PHONY: analyze
analyze:
	${MAKE} clean
	${MAKE} testdrivers ANALYZER="-fanalyzer -Wanalyzer-too-complex"

.PHONY: run
run: $(TSTFILES)
	-@rc=0; count=0; \
	for file in $(TSTFILES); do \
		echo "TEST	$$file"; ./$$file; \
		rc=`expr $$rc + $$?`; count=`expr $$count + 1`; \
	done; \
	echo; echo "Executed $$count tests	Failed tests $$rc"

.PHONY: testdrivers
testdrivers: $(TSTFILES)

-include $(HEADER_DEPS)
%.out: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TSTFILES) $(HEADER_DEPS)
