OBJECT=luatest

all: luatest csingle hipkg.so

hipkg.so: hipkg.c solua.lua
	 gcc -fPIC -shared -o $@ $<

csingle: csingle.c
	g++ -o $@ $< -ltolua++ -llua -Wall

luatest: luatest.c HelloLua.c luatest.lua
	g++ -o $@ luatest.c HelloLua.c -ltolua++ -llua -Wall

HelloLua.c: HelloWorld.pkg
	tolua++ -o $@ $<

clean:
	@rm -f HelloLua.c luatest csingle hipkg.so
