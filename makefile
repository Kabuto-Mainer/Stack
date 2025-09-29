//.PHONY: clean run build gitcom

flags = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

mod_work ?= -DMOD_WORK=DEBUG -DAUTO_REALLOC=ON -DCOMPLETION_DATA=ON -DHASH_SECURE=ON


S_stack.o: S_stack.cpp S_stack.h
	@(g++ -c S_stack.cpp $(mod_work) $(flags))
	@echo --- Compilation S_stack.cpp to S_stack.o finished successfully ---

main.o: main.cpp
	@(g++ -c main.cpp $(mod_work) $(flags))
	@echo --- Compilation main.cpp to main.o finished successfully---

C_calc.o: C_calc.cpp C_calc.h
	@(g++ -c C_calc.cpp $(mod_work) $(flags))
	@echo --- Compilation C_calc.cpp to main.o finished successfully---

support.o: support.cpp support.h
	@(g++ -c support.cpp $(mod_work) $(flags))
	@echo --- Compilation support.cpp to main.o finished successfully---


build: S_stack.o main.o C_calc.o support.o
	@(g++ S_stack.o main.o C_calc.o support.o $(mod_work) $(flags) -o main.exe)
	@echo --- Build main.exe finished successfully ---

run:
	@echo -- Running main.exe ---
	@(./main.exe)
	@echo --- Completion running main.exe ---

clean:
	@rm -rf *.o
	@echo -- All .o file have been deleted ---

gitcom:
	@(git add makefile color.h main.cpp main.exe S_stack.cpp S_stack.h C_calc.cpp C_calc.h test_proccec.txt)
	@echo -- Add file to git commit ---
	@(git commit -m "$(m)")
	@echo --- Git committing ---
	@(git push)
	@echo --- Git push ---


pros: clean
	$(MAKE) build mod_work="-DMOD_WORK=PROCESSOR -DAUTO_REALLOC=OFF -DCOMPLETION_DATA=OFF -DHASH_SECURE=OFF"

fstack: clean
	$(MAKE) build mod_work="-DMOD_WORK=DEBUG -DAUTO_REALLOC=ON -DCOMPLETION_DATA=ON -DHASH_SECURE=ON"

