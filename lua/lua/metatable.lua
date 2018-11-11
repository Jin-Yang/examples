#!/usr/bin/lua
a = {numerator=2, denominator=3}
b = {numerator=4, denominator=7}

fraction_op={}
function fraction_op.__add(f1, f2)
    ret = {}
    ret.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator
    ret.denominator = f1.denominator * f2.denominator
    return ret
end

setmetatable(a, fraction_op)
setmetatable(b, fraction_op)
s = a + b
print(s.numerator, s.denominator)

