#!/usr/bin/lua
function receive ()
    local status, value = coroutine.resume(producer)
    return value
end
function send (x)
    coroutine.yield(x)
end
producer = coroutine.create(function ()
    while true do
        local x = io.read()  -- 从文件中读取新的值
        send(x)              -- 将数据发送给消费者
    end
end)
function consumer ()
    while true do
        local x = receive()  -- 从生产者中接收新的值
        if x == nil then
            return 0
        else
            io.write(x, "\n")    -- 消费之
        end
    end
end

consumer()
