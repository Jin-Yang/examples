OBJECT=luatest

${OBJECT}: HelloLua.cpp test.lua
	g++ -o $@ main.cpp HelloLua.cpp -ltolua++ -llua

HelloLua.cpp: HelloWorld.pkg
	tolua++ -o $@ $<

test.lua:
	@echo "print (\"Hello World\")" > $@

clean:
	@rm -f HelloLua.cpp ${OBJECT}
