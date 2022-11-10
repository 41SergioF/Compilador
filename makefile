all :  rules.l rules.y
	clear
	flex -i rules.l
	bison rules.y
	gcc rules.tab.c -o out -lfl -lm
	./out