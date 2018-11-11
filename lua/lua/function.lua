#!/usr/bin/lua

--===== 可以返回多个值
function foobar()
    return "got", "something", "to"
end
w1, w2, w3, w4 = foobar() -- 最后一个值是nil
print(w1, w2, w3, w4)

--===== 局部函数，如下两个函数相同
function foo(x) return x^2 end
print(foo(12))
foo = function(x) return x^2 end
print(foo(12))

--===== 递归函数
function fib(n)
  if n < 2 then return 1 end
  return fib(n - 2) + fib(n - 1)
end
print(fib(10))

--===== 通过匿名函数实现闭包
function newCounter()
    local i = 0
    return function()     -- anonymous function
       i = i + 1
        return i
    end
end
c = newCounter()
print(c())  --> 1
print(c())  --> 2

--===== 同上
function myPower(x)
    return function(y) return y^x end
end
power2 = myPower(2)
power3 = myPower(3)
print(power2(4))  -- 4的2次方
print(power3(5))  -- 5的3次方
