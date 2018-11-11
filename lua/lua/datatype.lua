#!/usr/bin/lua

--+++++++++++++ TABLE
tbl = {"foobar", 123456, true, x=10, y=20, z=30, [3.14]="PI"}
--tbl[3.14] = "foobar"
for k, v in pairs(tbl) do                                 -- 遍历上述的全部变量
    print(k, v)
end

arr = {"ooops", 100, function() print("hello world") end}
arr[3]()                                                  -- 调用数组中的函数
for i=1, #arr do                                          -- 遍历数组，#表示获取数组大小
    print(arr[i])
end

foobar = {age=10, male=true, addr="earth"}                -- 如下是CRUD操作
foobar.name = "Foo Bar"                                   -- 新建
local age   = foobar.age                                  -- 获取
foobar.male = false                                       -- 修改
foobar.addr = nil                                         -- 删除
