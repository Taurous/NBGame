function func()
	print("Loaded Story Node " .. node_id .. "\n")
end

function interpret(str)
	if (str == "up") then
		return 2
	elseif (str == "left") then
		return 3
	elseif (str == "right") then
		return 4
	elseif (str == "down") then
		return 5
	elseif (str == "butts") then
		return 69
	else
		return nil
	end
end