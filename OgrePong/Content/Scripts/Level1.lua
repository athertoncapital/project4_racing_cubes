function destroySeeker(name)
	removeObject(name)
	removeScript(name .. "_script")

end



function createSeekerTrigger(name, x, y, z)
    x = x or 0
	y = y or z
	z = z or 30
	createTriggerArea(name, x, y, z)
	setTriggerSize(name, 10, 10, 10)
	setOnEnter(name, "if triggerObject == 'player' then  createSeeker('" .. name .. "_seeker', 50, 0, 50)  end")
	setOnExit(name, "if triggerObject == 'player' then  destroySeeker('" .. name .. "_seeker') end")
end

function createSeeker(name, x, y, z) 
	if name == nil then
		print("createSeeker:  name required!")
		return
	end
	x = x or 0
	y = y or 0
	z = z or 0
	
	print("Creating Seeker: ID = " .. name .. ",  Location: " .. tostring(x) .. ", " .. tostring(y) .. ",  " .. tostring(z))
	createObject("MyCube.mesh", name)
	setPosition(name, x, y, z)
	setObjectSize(name, 5,1,1)

	local seekerScript = Script.create()
	seekerScript.Think = function(this, time)
		local pX, pY, pZ = getPosition("player")
		local mX, mY, mZ =  getPosition(name)
		local deltaX, deltaY, deltaZ = pX-mX, pY-mY, pZ - mZ
		setVelocity(name, deltaX , deltaY, deltaZ)
	end	
	-- We are using the 
	addScript(seekerScript, name .. "_script")
end



createSeekerTrigger("testSeekerTrigger")