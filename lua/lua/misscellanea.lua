#!/usr/bin/lua

--- while
sum = 0
num = 1
while num <= 10 do
    sum = sum + num
    num = num + 1
end
print("While sum =",sum)

--- for .. start, end, step do ... end
for i = 1, 100, 2 do
    sum = sum + i
end
print('For sum =', sum)

--- repeat .. until ..
sum = 2
repeat
    sum = sum ^ 2                            --- exponent operation
until sum > 1000
print("Repeat sum = ", sum)

--- if .. elseif .. else .. end
age = 20
sex = 'Male'
if age == 40 and sex == "Male" then
    print("Perfect!!!")
elseif age > 60 and sex ~= "Female" then     --- ~= is not equal, NOT !=
    print("Old man")
else
    io.write("input your age: ")             --- io library, read/write from stdio/stdout
--    local age = io.read()
    print("Your age is "..age)               --- .. join operation
end

--- recursion
function fib(n)
    if n < 2 then return 1 end
    return fib(n - 2) + fib(n - 1)
end
print('Recursion result: '..fib(10))

--- closure function, 1
function newCounter()
    local i = 0
    return function()                        --- anonymous function
        i = i + 1
        return i
    end
end
c1 = newCounter()
print(c1())      --> 1
print(c1())      --> 2
--- closure function, 2
function myPower(x)
    return function(y) return y^x end
end
power2 = myPower(2)
power3 = myPower(3)
print(power2(4)) --4的2次方
print(power3(5)) --5的3次方

--- multi assignment
name, age, bGay = "haoel", 37, false, "haoel@hotmail.com"     -- the forth will be ignored.
function getUserInfo(id)
    print(id)
    return "haoel", 37, "haoel@hotmail.com", "http://coolshell.cn"
end
name, age, email, website, bGay = getUserInfo()               -- id and bGay will be nil.

--- the following functions are same.
function foo(x) return x^2 end
foo = function(x) return x^2 end


