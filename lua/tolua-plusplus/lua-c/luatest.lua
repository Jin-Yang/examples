print ("now in lua script!\ntry to print 'Arr' by name:")
print (Arr)
print ("and also print 'Arr':")
--print contents of Arr
for i=0,9 do print (Arr[i]) end

--change contents of Arr
print ("now change the Arr.")
for i=0,9 do Arr[i] = i*2 end

print_sth()
