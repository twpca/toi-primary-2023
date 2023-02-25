CC = g++
CCARGS = -DEVAL -Wall -Wshadow -Wconversion -std=gnu++17 -O2 -pipe -static -s
SOLUTION_LIST = \
	molecule_brain \
	storm_nlgn_klgn \
	house_nlgn_nm

.PHONY: clean $(SOLUTION_LIST)

all: ${SOLUTION_LIST:%=%.exe}

${SOLUTION_LIST:%=%.exe}: %.exe: %.cpp
	$(CC) $^ $(CCARGS) -o $@

$(SOLUTION_LIST): %: %.exe
	$(info haha)

${SOLUTION_LIST:%=run_%}: run_%: %.exe
	./$^

clean:
	rm -f $(SOLUTION_LIST:%=%.exe)
