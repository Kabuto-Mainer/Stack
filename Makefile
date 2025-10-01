#//.PHONY: clean run build gitcom

flags = -D_DEBUG -Werror -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


#! Изменить на без связей
processor:
	@echo -------------------------------------------------------------------------
	g++ processor.cpp stack.cpp support.cpp $(flags) -o processor.exe

compiler:
	@echo -------------------------------------------------------------------------
	g++ compiler.cpp support.cpp $(flags) -o compiler.exe

run-c:
	@echo -------------------------------------------------------------------------
	./compiler.exe

run-p:
	@echo -------------------------------------------------------------------------
	./processor.exe

gitcom:
	@(git add Makefile color.h stack.cpp stack.h processor.cpp processor.h compiler.h compiler.cpp stack_define.h const.h comand.h text_code.txt bin_code.asm input.txt)
	@echo -- Add file to git commit ---
	@(git commit -m "$(m)")
	@echo --- Git committing ---
	@(git push)
	@echo --- Git push ---
#
#
# speed: clean
# 	$(MAKE) build own_flags="-DMOD_WORK=PROCESSOR -DAUTO_REALLOC=OFF -DCOMPLETION_DATA=OFF -DHASH_SECURE=OFF -DBIRD_SECURE=OFF"
#
# slow: clean
# 	$(MAKE) build own_flags="-DMOD_WORK=DEBUG -DAUTO_REALLOC=ON -DCOMPLETION_DATA=ON -DHASH_SECURE=ON -DBIRD_SECURE=OFF"
#
