#!/usr/bin/lua
function receive (prod)
    local status, value = coroutine.resume(prod)
    return value
end
function send (x)
    coroutine.yield(x)
end
function producer ()
    return coroutine.create(function ()
        while true do
            local x = io.read()    -- 从文件中读取新的值
            send(x)                -- 将数据发送给消费者
        end
    end)
end
function filter (prod)
    return coroutine.create(function ()
        for line = 1, math.huge do
            local x = receive(prod)
            if x ~= nil then
                x = string.format("%5d %s", line, x)
            end
            send(x)
        end
    end)
end
function consumer (prod)
    while true do
        local x = receive(prod)    -- 从生产者中接收新的值
        if x == nil then
            return 0
        else
            io.write(x, "\n")      -- 消费之
        end
    end
end
----- 其调用过程大致如下
p = producer()
f = filter(p)
consumer(f)
----- 也可以简单写为
--consumer(filter(producer()))
