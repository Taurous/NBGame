function func()
	print("Loaded Story Node " .. node_id .. ".")
end

function interpret(str)
	print("You entered: " .. str .. ".")
	
	v = nil
	
	if (str == "up") then
		v = 2
	elseif (str == "left") then
		v = 3
	elseif (str == "right") then
		v = 4
	elseif (str == "down") then
		v = 5
	elseif (str == "butts") then
		v = 69
	end
	
	if (v ~= nil) then
		print("The next node is " .. v .. ".")
	else
		print("That is not an option.\n")
	end
end