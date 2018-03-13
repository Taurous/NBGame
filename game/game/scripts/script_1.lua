function func()
	print("Loaded Story Node " .. node_id .. ".")
end

function interpret(str)
	--print("You entered: " .. str .. ".")
	
	v = nil
	
	if (str == "up") then
		v = 1
		print("You cannot go that way.")
	elseif (str == "left") then
		v = 5
		print("You move left.")
	elseif (str == "right") then
		v = 6
		print("You move right.")
	elseif (str == "down") then
		v = 0
		print("You move down.")
	end
	
	if (v == nil) then
		print("That is not an option.")
	end
	
	return v
end