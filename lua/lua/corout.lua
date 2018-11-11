#!/usr/bin/lua
print("##### 1 #####")
co = coroutine.create(function () print("Hello World") end)
print(co)                      --> thread: 0x24a0b20
print(coroutine.status(co))    --> suspended
coroutine.resume(co)           --> hi
print(coroutine.status(co))    --> dead


print("\n##### 2 #####")
co = coroutine.create(function ()
    for i = 1, 3 do
        print("co", i)
        coroutine.yield()
    end
end)
coroutine.resume(co)        --> co      1
print(coroutine.status(co)) --> suspended
coroutine.resume(co)        --> co      2
coroutine.resume(co)        --> co      3
coroutine.resume(co)        --> prints nothing
print(coroutine.resume(co)) --> false cannot resume dead coroutine

print("\n##### 3 #####")
co = coroutine.create(function (a, b, c)
    print("co", a, b, c + 2)
end)
print(coroutine.resume(co, 1, 2, 3)) --> co   1   2   5
                                     --> true
co = coroutine.create(function (a, b)
    coroutine.yield(a+b, a-b)
end)
print(coroutine.resume(co, 20, 10)) --> true  30  10

co = coroutine.create (function (x)
    print("co1", x)
    print("co2", coroutine.yield())
end)
coroutine.resume(co, "hi") --> co1 hi
coroutine.resume(co, 4, 5) --> co2 4 5
