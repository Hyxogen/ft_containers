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
CXX		:= clang++
WARNINGS	:= -Wall -Wextra -Werror -std=c++98 -pedantic -Wuninitialized \
			-Wmissing-include-dirs -Wshadow -Wundef -Winvalid-pch \
			-Winit-self -Wswitch-enum -Wswitch-default -Wformat=2 \
			-Wformat-nonliteral -Wformat-security -Wformat-y2k \
			-Wdouble-promotion -Wfloat-equal -Wpointer-arith \
			-Wstrict-overflow=5 -Wcast-qual -Wcast-align -Wconversion \
			-Wpacked -Wstrict-aliasing -fstrict-aliasing \
			-Wredundant-decls -Wmissing-declarations \
			-Wmissing-field-initializers -Wwrite-strings \
			-Wstack-protector -fstack-protector -Winline \
			-Waggregate-return -Wbad-function-cast -Wc++-compat \
			-Wzero-as-null-pointer-constant -Wctor-dtor-privacy \
			-Wold-style-cast -Woverloaded-virtual \
			-Warc-repeated-use-of-weak -Wbitfield-enum-conversion \
			-Wclass-varargs -Wconditional-uninitialized \
			-Wthread-safety -Wconsumed -Wdirect-ivar-access \
			-Wdisabled-macro-expansion -Wembedded-directive \
			-Wexpansion-to-defined \
			-Wformat-pedantic -Widiomatic-parentheses \
			-Winconsistent-missing-destructor-override \
			-Winfinite-recursion -Wlocal-type-template-args \
			-Wloop-analysis -Wmethod-signatures -Wmismatched-tags \
			-Wmissing-braces -Wmissing-prototypes \
			-Wmissing-variable-declarations -Wmost -Wmove \
			-Wnonportable-system-include-path \
			-Wnull-pointer-arithmetic -Wover-aligned \
			-Woverriding-method-mismatch -Wpch-date-time -Wpragmas \
			-Wreserved-id-macro -Wreserved-user-defined-literal \
			-Wretained-language-linkage \
			-Wsemicolon-before-method-body -Wsometimes-uninitialized \
			-Wstring-conversion -Wsuper-class-method-mismatch \
			-Wtautological-compare -Wundefined-reinterpret-cast \
			-Wunreachable-code -Wunreachable-code-break \
			-Wunreachable-code-loop-increment \
			-Wunreachable-code-return -Wvector-conversion -Wcomma \
			-Wduplicate-enum -Wduplicate-method-arg \
			-Wduplicate-method-match -Wdynamic-exception-spec \
			-Wempty-translation-unit -Wexplicit-ownership-type \
			-Wignored-qualifiers -Wimplicit -Wkeyword-macro \
			-Wnewline-eof -Wredundant-parens -Wstatic-in-inline \
			-Wstrict-prototypes -Wweak-template-vtables \
			-Wzero-length-array -Warray-bounds-pointer-arithmetic \
			-Winvalid-offsetof -Wflexible-array-extensions \
			-Wfloat-conversion -Wfloat-overflow-conversion \
			-Wfloat-zero-conversion -Wshorten-64-to-32 -Wsign-compare \
			-Wsign-conversion -Wcomment -Wdocumentation \
			-Wdocumentation-pedantic -Wgnu \
			-Wheader-hygiene -Wunneeded-internal-declaration \
			-Wunneeded-member-function -Wvla -Wshift-overflow \
			-Wshift-negative-value -Wnull-dereference -Wunused-macros \
			-Wextra-semi
ANALYZER	:=
SANITIZERS	:= -fsanitize=address,undefined,integer
CXXFLAGS	:= -std=c++98 $(WARNINGS) $(ANALYZER) $(SANITIZERS) -I../include \
			-Isupport -MMD -MP -DFT_TEST -O0 -g3 -DFT_DEBUG

CXXFILES	:= $(shell find . -type f -name '*.cpp')
HEADER_DEPS	:= $(CXXFILES:.cpp=.d)
TSTFILES	:= $(CXXFILES:.cpp=.out)

BIN_DIR		:= bin

.PHONY:	all
all: run

.PHONY: analyze
analyze:
	${MAKE} clean
	${MAKE} testdrivers ANALYZER="-fanalyzer"

.PHONY: run
run: $(TSTFILES)
	-@rc=0; count=0; res=0; \
	for file in $(TSTFILES); do \
		./$$file; \
		res="$$?"; \
		if [ "$$res" -eq 0 ]; \
		then printf PASSED; \
		else printf FAILED; \
		fi; \
		echo "	$$file"; \
		rc=`expr $$rc + $$(($$res != 0))`; count=`expr $$count + 1`; \
	done; \
	echo; echo "Executed $$count tests	Failed tests $$rc"

.PHONY: testdrivers
testdrivers: $(TSTFILES)

-include $(HEADER_DEPS)
%.out: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TSTFILES) $(HEADER_DEPS)
