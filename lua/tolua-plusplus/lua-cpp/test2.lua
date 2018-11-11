print ("now in lua")

--new a CNumber Object
print ("now allocate a CNumer object:")
num = CNumber:new()
num2 = CNumber:new(222)
print ("init,num:"..num:GetNumber())
print ("init,num2:"..num2:GetNumber())

-- set number
print("now call SetNumber()")
num:SetNumber(6)
print("set number:"..num:GetNumber())

-- delete object
num:delete()
print("num is deleted,access GetNumber is invalid!")
print("invalidcall,result:"..num:GetNumber())

-- new a CMessage Object
msg=CMessage:new()
print("init msg:"..msg:GetMessage())

-- set message
print("msg:SetMessage('changed message')")
msg:SetMessage("changed message")
print("now msg:"..msg:GetMessage())
msg:ShowMessage()
msg:delete()
